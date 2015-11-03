#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <jpeglib.h>
#include <onion/extras/png.h>
#ifdef WEB_DISPLAY_USES_JPEG
#define JPEG_QUALITY 80
#include <onion/extras/jpeg.h>
#endif
#include "ImageAnalysis.h"



ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice, SettingKinect* pSettingKinect):
	m_pSettingKinect(pSettingKinect),
//	m_depthMat(Size(KRES_X,KRES_Y),CV_16UC1),
	m_depthf  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_filterMat  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_depthMask  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_depthMaskWithoutThresh  (Size(KRES_X,KRES_Y),CV_8UC1),//backup to generate new deptMask
	m_depthMask16U  (Size(KRES_X,KRES_Y),CV_16UC1),// = (m_depthMask - b)/a
	m_filteredMat  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_areaMask  (Size(KRES_X,KRES_Y),CV_8UC1), //mask of areas, ids=0,1,..., offcut=255
	m_rgb  (Size(KRES_X,KRES_Y),CV_8UC3),
	m_areaGrid  (Size(KRES_X,KRES_Y),CV_8UC1), //binary image of obstacles
	m_area_detection_mask  (Size(KRES_X+2,KRES_Y+2),CV_8UC1),
  m_areaCol_ok(false),
	m_maskFront_ok(false),
	m_area_detection_step(0),
	m_png_redraw(false),
	m_png_scale(-1),
	m_png_imgC1  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_png_imgC3  (Size(KRES_X,KRES_Y),CV_8UC3),
	m_png_mutex(),
	m_pdevice(pdevice),
	m_depthMaskCounter(-NMASKFRAMES)//use -depthMaskCounter Frames as mask
{
	m_depthMask = Scalar(255);//temporary full mask
	m_areaMask = Scalar(0);
	m_areaGrid = Scalar(255);

  // Fill buffer images to find them easer during debugging.
	m_png_imgC1 = Scalar(128);
	m_png_imgC3 = Scalar(0, 255, 0);
}

ImageAnalysis::~ImageAnalysis()
{
}

FunctionMode ImageAnalysis::depth_mask_detection(){
	//printf("depth mask detection\n");
	
	if( m_depthMaskCounter > 0){
		// Depth mask already detected. Reset m_depthMaskCounter and begin again.
		m_depthMaskCounter = -NMASKFRAMES;
	}
	if( m_depthMaskCounter == -NMASKFRAMES ){
		/* First step/frame. */
		
		//Disable clipping in libfreenect driver to get depth mask of
		//full range.
		m_pdevice->setRoi(false,Rect(0,0,0,0) );
	
		m_depthMaskWithoutThresh = Scalar(0);
		m_depthMask = Scalar(255);//temporary full mask
	}
	if( m_depthMaskCounter < 0){
		// Use (fullsize) early frames to generate mask
		m_pdevice->getDepth8UC1(m_depthf, Rect(0,0,KRES_X,KRES_Y),
				m_pSettingKinect->m_kinectProp.minDepth,m_pSettingKinect->m_kinectProp.maxDepth);
		if( m_depthMaskCounter > 2-NMASKFRAMES)//deprecated filtering of first frames
			createMask(m_depthf,m_depthMaskWithoutThresh,/*m_pSettingKinect->m_kinectProp.marginBack,*/m_depthMaskWithoutThresh);
		m_depthMaskCounter++;

		if( m_depthMaskCounter == 0 ){
			/* Last step/frame. */
			finishDepthMaskCreation();

			/* Re-enable clipping */
			if( m_pSettingKinect->m_kinectProp.clipping)
				m_pdevice->setRoi(true,m_pSettingKinect->m_kinectProp.roi);

			printf("Depth mask detection finished.\n");
			return HAND_DETECTION;
		}
		return DEPTH_MASK_DETECTION;
	}else{
		return HAND_DETECTION;
	}
		return DEPTH_MASK_DETECTION;
}

FunctionMode ImageAnalysis::hand_detection()
{
//	printf("hand detection\n");
	if( m_depthMaskCounter < 0)
		return depth_mask_detection();

	Rect roi = m_pSettingKinect->m_kinectProp.roi;

	m_png_mutex.trylock(); //Block png creation (avoid flickering)

	// Analyse Roi of depth frame
	if(m_pSettingKinect->m_kinectProp.directFiltering){
		Mat fMRoi(m_filteredMat,roi);
		Mat dMRoi16U(m_depthMask16U,roi);
		/* Direct evaluation of masked deptframe.
		Advantages: Faster.
		Disadvantages: No depth frame, no bluring.
		*/
		//m_pdevice->getDepth8UC1(fMRoi, roi,
		//		m_pSettingKinect->m_kinectProp.minDepth,m_pSettingKinect->m_kinectProp.maxDepth, dMRoi);
		while(! m_pdevice->getDepth8UC1_b(fMRoi, roi, m_pSettingKinect->m_rangeMap, dMRoi16U))
		//while(! m_pdevice->getDepth8UC1_b(fMRoi, roi, m_pSettingKinect->m_kinectProp.minDepth, m_pSettingKinect->m_kinectProp.maxDepth, dMRoi16U))
		{
			//printf(" Bad, get old frame!\n");
			usleep(50);		
		}

	}else{
		Mat dfRoi(m_depthf,roi);
		Mat fMRoi(m_filteredMat,roi);
		Mat dMRoi(m_depthMask,roi);
		while(! m_pdevice->getDepth8UC1(dfRoi, roi,
				m_pSettingKinect->m_kinectProp.minDepth,m_pSettingKinect->m_kinectProp.maxDepth))
		{
			//printf(".");
			usleep(50);
		}
		//printf("\n");

		//filter image
		filter(dfRoi,dMRoi,80,fMRoi);
	}

	m_png_mutex.unlock();

	return HAND_DETECTION;
}

FunctionMode ImageAnalysis::area_detection(Tracker *tracker)
{
	/* Too small values lead to flawed detections. We backup the 
	 * user value and restore it later. */
	int backupMinBlobSize = m_pSettingKinect->m_kinectProp.minBlobArea;

	switch (m_area_detection_step) {
	case 2:
		{// Wait util no blob is detected.
			//printf("area detection 2\n");
			hand_detection();
			m_pSettingKinect->m_kinectProp.minBlobArea = max(backupMinBlobSize,256);
			tracker->trackBlobs(m_filteredMat(m_pSettingKinect->m_kinectProp.roi), m_areaMask, true, NULL);
			m_pSettingKinect->m_kinectProp.minBlobArea = backupMinBlobSize;
			if( tracker->getBlobs().size() == 0 ){
				m_area_detection_step = 1;
			}
		} break;
	case 3://for AREA_DETECTION_END
		{
			//printf("area detection 3\n");
			m_area_detection_step = 3;
			repoke_finish();
			return HAND_DETECTION;
		} break;
	case 0:
		{
			printf("area detection 0\n");
			repoke_init();
			genColoredAreas();
			m_area_detection_step = 1;
		}//no break!
	case 1:
		{
			//printf("area detection 1\n");
			//Mat& depth = m_depthMaskWithoutThresh;
			hand_detection();
			m_pSettingKinect->m_kinectProp.minBlobArea = max(backupMinBlobSize,256);
			tracker->trackBlobs(m_filteredMat(m_pSettingKinect->m_kinectProp.roi), m_areaMask, true, NULL);
			m_pSettingKinect->m_kinectProp.minBlobArea = backupMinBlobSize;
			std::vector<cBlob>& blobs = tracker->getBlobs();

			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].event != BLOB_MOVE) continue;
				if( blobs[i].areaid == 1 ){
					/* detection finshed. */
					m_area_detection_step = 0;

					//reset pixels with MAXAREAS+1 value
					repoke_finish();
					//clear blobs to begin fresh in hand detection.
					blobs.clear();
					return HAND_DETECTION;
				}
			}
			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].event != BLOB_MOVE) continue;
				if( blobs[i].areaid == MAXAREAS+1 ){
					//found new blob without area
					Area area;
					area.id = m_area_detection_areas.size()+1;
					area.repoke_x = blobs[i].location.x+m_pSettingKinect->m_kinectProp.roi.x;
					area.repoke_y = blobs[i].location.y+m_pSettingKinect->m_kinectProp.roi.y;

					if( ! repoke_step(area) )
						return AREA_DETECTION;

					m_area_detection_step = 2;
					break;
				}
			}
		}break;
	default:
		{
			printf("Unknown state during area detection\n");
		}break;
	}

	return AREA_DETECTION;
}
//++++++++

void ImageAnalysis::genFrontMask(){
	m_areaGrid = Scalar(255/*0*/);
	Rect roi = m_pSettingKinect->m_kinectProp.roi;
	Mat agRoi(m_areaGrid,roi);
	Mat dfRoi(m_depthf,roi);
	Mat tmp(dfRoi.size(),dfRoi.type());
//	Mat newAreaGrid = Mat(Size(roi.width,roi.height), CV_8UC1);
	int nFrames = 10;
	for(int i=0;i<nFrames; i++){
		m_pdevice->getDepth8UC1(dfRoi, roi,
				m_pSettingKinect->m_kinectProp.minDepth,m_pSettingKinect->m_kinectProp.maxDepth);
		Mat Kernel(Size(9, 9), CV_8UC1); Kernel.setTo(Scalar(1));
		Mat Kernel2(Size(7, 7), CV_8UC1); Kernel2.setTo(Scalar(1));
		dilate(dfRoi, tmp, Kernel); 
		erode(tmp, tmp, Kernel2); 
		//threshold(dfRoi, dfRoi,255-m_pSettingKinect->m_kinectProp.marginFront,255,THRESH_BINARY);
		//agRoi = min/*max*/(agRoi,dfRoi);
		threshold(tmp, tmp,255-m_pSettingKinect->m_kinectProp.marginFront,1,THRESH_BINARY_INV);
		agRoi -= tmp;
	}
	/* convert agRoi back to 0-255-Img */
	threshold(agRoi, agRoi,255-(2*nFrames/3+1),255,THRESH_BINARY);

  m_maskFront_ok = true;
}

void ImageAnalysis::genColoredAreas(){
	m_areaCol = Scalar(0,0,0);
	Mat col(Size(640,480),CV_8UC3);
	int r,g,b;

	Mat m = (m_areaMask==MAXAREAS+1);
	r = 0; g = 255; b = 200;
	col = Scalar(b,g,r);
	col.copyTo(m_areaCol,m);

	//for(int i=0; i<m_areas.size(); i++){
	for(int i=0; i<MAXAREAS; i++){
		Mat m = (m_areaMask==i+1);
		r = AREACOLORS[i%10][0];
		g = AREACOLORS[i%10][1];
		b = AREACOLORS[i%10][2];
		col = Scalar(b,g,r);
		col.copyTo(m_areaCol,m);
		m_areaCol_ok = true;
	}

}


Mat& ImageAnalysis::getColoredAreas(){
	if( !m_areaCol_ok ) genColoredAreas();


	IplImage gray = m_depthf;
	IplImage rgb = m_rgb;
	cvMerge(&gray, &gray, &gray, NULL, &rgb);
	addWeighted(m_rgb,0.5f,m_areaCol,0.5f,0,m_rgb);
	return m_rgb;
}

Mat& ImageAnalysis::getFrontMask(){
	if( !m_maskFront_ok ) genFrontMask();
	return m_areaGrid;
}
/*
 * Reset internal counter of mask detection and clear mask.
 * New mask will generated.
 */
void ImageAnalysis::resetMask(SettingKinect* pSettingKinect, int changes){
	if( changes & FRONT_MASK ){
		m_maskFront_ok = false;
		//std::cout << "Generation of front mask" << std::endl;
		//genFrontMask();
	}

	if( changes & (MASK|MOTOR|CONFIG) ){
	/* Start all steps of depth mask detection. */
		printf("ImageAnalysis: Create new mask\n");
		//m_depthMaskWithoutThresh = Scalar(0);
		//m_depthMask = Scalar(255);//temporary full mask
		m_depthMaskCounter = -NMASKFRAMES;
	}else	if( changes & BACK_MASK ){
	/* Invoke last step of depth mask detection. */
		//recreate mask m_depthMask and m_depthMask16U from m_depthMaskWithoutThresh
		finishDepthMaskCreation();
	}

	if( changes & MARGIN ){
		//printf("ImageAnalysis: Change thresh val\n");
			//addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_kinectProp.marginBack, m_depthMask);
	}
	if( changes & TUIO_PROTOCOL ){
		//TODO, but not here...
	}
	if( changes & REPOKE ){
		std::vector<Area>& areas = m_pSettingKinect->m_areas;
		if( areas.size() > 0 ){
			repoke_init();
			for(int i=0; i<areas.size(); i++){
				printf("Repoke of area %i. Midpoint: %f %f", areas[i].id, areas[i].repoke_x, areas[i].repoke_y );
				repoke_step( areas[i] );
			}
			repoke_finish();
		}

	}
}

void ImageAnalysis::repoke_init(){
			// generate binary image for area detection, if not set
			getFrontMask();

			//2pixel wider and taller for floodfill
			m_area_detection_mask = Scalar(0);
			//reset area mask and set full roi to one big area
			m_areaMask = Scalar(0);
			/* Set value in Roi to MAXAREAS+1. (Tracker ignore blobs in area=0) */
			m_areaMask(m_pSettingKinect->m_kinectProp.roi) = Scalar(MAXAREAS+1);
			m_area_detection_areas.clear();

			genColoredAreas();
}

/* Set area.id before you call this method */
bool ImageAnalysis::repoke_step(Area& area){
	/* Flood fill of (old) depth image to detect area. use m_area_detection_mask as mask
	 * to avoid overlapping of areas. Flag CV_FLOODFILL_MASK_ONLY is set to avoid changes
	 * in m_depthMask.
	 * TODO: Looping of FloodFill with different low-high-values can improve results.
	 * TODO: Limit floodFill to Roi.
	 */
	Rect cc;
	floodFill(m_areaGrid/*m_depthMask*/, m_area_detection_mask, cvPoint(area.repoke_x, area.repoke_y),
			Scalar(255), &cc, Scalar(0)/*low*/, Scalar(0)/*up*/, 4+FLOODFILL_MASK_ONLY);

	area.rect = cc;
	area.color = Scalar( AREACOLORS[area.id%10][0], AREACOLORS[area.id%10][1], AREACOLORS[area.id%10][2]);
	area.area = cc.width*cc.height;
	
	if( area.area < 800.0 ){
		printf("Area %i to small.\n", area.id);
		return false;
	}
	if( area.area > 0.95*m_pSettingKinect->m_kinectProp.roi.width * m_pSettingKinect->m_kinectProp.roi.height ){
		printf("Area %i very big and ignored. Depth mask ok?\n", area.id );
		return false;
	}

	/* cc2=cc+Border. cc2 is used to left space for some border detection in (2) */
	int l = max(cc.x-2,0); int t = max(cc.y-2,0);
	int r = min(cc.x+cc.width+2,KRES_X); int b = min(cc.y+cc.height+2,KRES_Y);
	Rect cc2(l,t,r-l,b-t);

	//Mat changeable = (m_areaMask(cc)==MAXAREAS+1);//cut of other areas
	Mat changeable = (m_areaMask(cc2)==MAXAREAS+1);//cut of other areas
	//get new !=0 values of m_area_detection_mask
	changeable = min(changeable, m_area_detection_mask(
				//Rect(cc.x+1,cc.y+1,cc.width,cc.height)//shift by (1,1)
				Rect(cc2.x+1,cc2.y+1,cc2.width,cc2.height)//shift by (1,1)
				));

	changeable *= area.id;
	//Mat areaMaskDst = m_areaMask(cc);
	Mat areaMaskDst = m_areaMask(cc2);
	changeable.copyTo( areaMaskDst, changeable );
	genColoredAreas();

	/* (2) Find depth information of the obstacle. Simply search minimal depth along the border of the area.
	*/
	Mat border(changeable.size(),changeable.type());
	Mat Kernel(Size(3, 3), CV_8UC1); Kernel.setTo(Scalar(1));
	dilate(changeable, border , Kernel);
	border = border - changeable ;
	//Scalar avg = mean( m_depthf(area.rect), border(area.rect) );
	Scalar avg = mean( m_depthMask(cc2)/*m_depthf*/, border );
	printf("Avarage depth of area border: %f\n", avg[0] );
	area.depth = (int)avg[0];

	printf("Add Area %i\n",area.id);
	m_area_detection_areas.push_back(area);
	return true;
}

void ImageAnalysis::repoke_finish(){
	//reset pixels with MAXAREAS+1 value
	//printf("Reset!!\n");
	threshold(m_areaMask, m_areaMask,MAXAREAS,0,THRESH_TOZERO_INV);
	genColoredAreas();

	//update depthMask, if depthMask depends from areaMask
	addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_kinectProp.marginBack, m_depthMask);
	if( m_pSettingKinect->m_kinectProp.areaThresh ){
		addAreaThresh(m_pSettingKinect->m_areas, m_areaMask, m_depthMask);
	}

	//set m_areas and update jSON description of m_areas.
	m_pSettingKinect->setAreas(m_area_detection_areas);
}
/*
 * Set for each area the pixels to area.depth. Position of areas will extract from areaMask.
 * Function should not called frequently.
 * */
void ImageAnalysis::addAreaThresh(/*Mat& src,*/ std::vector<Area> areas, Mat& areaMask,  Mat& dst){
	Mat v(dst.size(),dst.type());
	for( int i=0; i<areas.size(); i++){
		printf("Depth of area %i: %i\n",i+1,areas[i].depth);
		/* The minus value:
		 * The detection should begin "short" behind the frame. The minDepth and
		 * maxDepth value affect the depth unit length. Thus, this values need to be consides.
		 * */
		v = Scalar(areas[i].depth-
				0.5 * (255/(m_pSettingKinect->m_kinectProp.maxDepth-m_pSettingKinect->m_kinectProp.minDepth) )
				);
		Mat a = (areaMask == areas[i].id);
		v.copyTo(dst,a);
	}
}

/*
 * Eval m_depthMask and m_depthMask16U from m_depthMaskWithoutThresh.
 * Thats the last step during the depth mask decetion. Moreover,
 * it will called if m_marginBack, m_areaThresh or m_directFiltering
 * updated.
 */
void ImageAnalysis::finishDepthMaskCreation(){
	addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_kinectProp.marginBack, m_depthMask);
	if( m_pSettingKinect->m_kinectProp.areaThresh ){
		//add local thresh val for every detected area
		addAreaThresh(m_pSettingKinect->m_areas, m_areaMask, m_depthMask);
	}

	//getFrontMask();
	/* Debug 2014, add frame as mask. This is required for directFiltering mask. */
	//m_depthMask = max(m_depthMask,getFrontMask());//this would be bad for hand blobs which overlap the borders

	/* Set up m_depthMask16U for directFiltering mode */
	//remap mask to 16UC1 format.
	int m = m_pSettingKinect->m_kinectProp.minDepth;
	int M = m_pSettingKinect->m_kinectProp.maxDepth;
	float alphaInv = ( M-m )/( 0.0-255.0 );
	float betaInv = ( m*0 - M*255.0 )/(0-255);
	m_depthMask.convertTo(m_depthMask16U, CV_16UC1, alphaInv, betaInv);

	m_depthMaskCounter = 0;
}


typedef Vec<uchar, 4> VT;

int ImageAnalysis::http_actions(Onion::Request *preq, int actionid, Onion::Response *pres){

	switch(actionid){
		case HTTP_ACTION_REGENERATE_MASKS:
			{ /* Regenerate masks */
				resetMask( m_pSettingKinect, MASK|FRONT_MASK);
				std::string reply("ok");
				pres->write(reply.c_str(), reply.size() );
				return 0;
			}
			break;
		default:
			break;
	}
	return -3;
}

// Handler for DISPLAY_MODE_WEB.
int ImageAnalysis::getWebDisplayImage(Onion::Request *preq, int actionid, Onion::Response *pres){

	switch(actionid){
		case HTTP_ACTION_SELECT_VIEW:
			{ 
				//VPRINT("HTTP_ACTION_SELECT_VIEW: Reset redraw flag.\n");
				m_png_redraw = true; 
				// action handled by OnionServer::updateWebserver, too.
				return -3;
			}
			break;
		case HTTP_ACTION_GET_PREVIEW_IMAGE:
			{ /* Generate image */
				int scale = atoi( onion_request_get_queryd(preq->c_handler(),"scale","100") );
				const char *force = onion_request_get_queryd(preq->c_handler(),"force","0");

				std::string key("Content-Type");
#ifdef WEB_DISPLAY_USES_JPEG
				std::string mimetype("image/jpeg");
#else
				std::string mimetype("image/png");
#endif
				// Set header which informs that the image should not read from cache.
				// Required in Chrome (Nov, 2015). 
				pres->setHeader(key,mimetype);
				pres->setHeader("Cache-Control", " no-store,max-age=0, must-revalidate");

				//check if image generation is forced
				if( *force == '1' ) m_png_redraw = true;
				m_png_mutex.lock();
				//here, m_png_redraw could be false (second image request at the same time).

				VPRINT("redraw: %i, scale: %i, newscale: %i", m_png_redraw?1:0, m_png_scale, scale);

				if( !m_png_redraw && scale==m_png_scale ){
					VPRINT("No new preview image. Send 1x1 dummy image.\n");
					//There was no change between the last sended image.
					//std::string reply = "noNewImage";
					//onion_response_write(res, reply.c_str(), reply.size() ); 
					unsigned char image[4];
					image[0] = 0; image[1] = 0; image[2] = 0; image[3] = 0;
#ifdef WEB_DISPLAY_USES_JPEG
					onion_jpeg_response( image , 4, JCS_EXT_RGBX, 1, 1, JPEG_QUALITY, pres->c_handler() );
#else
					onion_png_response( image, 4, 1, 1, pres->c_handler() );
#endif
					m_png_mutex.unlock();
					return 0;
				}

				if( /*m_pSettingKinect->m_withKinect == false ||*/
						m_pSettingKinect->m_displayMode != DISPLAY_MODE_WEB ||
						m_pSettingKinect->m_view == VIEW_NONE){
					//Display is not active
					//generate 1x1 pixel
					unsigned char image[4];
					image[0] = 0; image[1] = 0; image[2] = 0; image[3] = 0;
#ifdef WEB_DISPLAY_USES_JPEG
					onion_jpeg_response( image , 4, JCS_EXT_RGBX, 1, 1, JPEG_QUALITY, pres->c_handler() );
#else
					onion_png_response( image, 4, 1, 1, pres->c_handler() );
#endif
					m_png_mutex.unlock();
					m_png_redraw = false;
					return 0;
				}


				VPRINT("(PNG/JPG) View: %i\n", m_pSettingKinect->m_view);
				int channels = 1;//4=RGBA, -4=ABRG 
				Mat* png = NULL;
				switch (m_pSettingKinect->m_view){
					case VIEW_RGB:
						channels=4;
						//cv::swap( m_rgb, m_png_imgC3);
						std::swap( m_rgb, m_png_imgC3);
						png=&m_png_imgC3;
						break;
					case VIEW_AREAS:
						channels=4;
						//png=&m_areaCol;
						getColoredAreas();
						png=&m_rgb;
						break;
					case VIEW_MASK:
						//std::swap( m_depthMask, m_png_imgC1);
						//m_png_imgC1 = m_depthMask;
						png=&m_depthMask;
						break;
					case VIEW_FILTERED:
						std::swap( m_filteredMat, m_png_imgC1);
						//m_png_imgC1 = m_filteredMat;
						png=&m_png_imgC1;
						break;
					case VIEW_FRONTMASK:
						png=&getFrontMask();
						break;
					case VIEW_DEPTH:
					default:
						std::swap( m_depthf, m_png_imgC1);
						//m_png_imgC1 = m_depthf;
						png=&m_png_imgC1;
						break;
				}


				Rect roi = m_pSettingKinect->m_kinectProp.roi;

				// Return empty file if selected image does not contain data.
				if( png == NULL || png->empty() /*|| png->size().width == 0 || png->size().height == 0*/ ){
					VPRINT("No image available.\n");
					//generate 1x1 pixel image
					unsigned char image[4];
					image[0] = 0; image[1] = 0; image[2] = 0; image[3] = 0;
#ifdef WEB_DISPLAY_USES_JPEG
					onion_jpeg_response( image , 4, JCS_EXT_RGBX, 1, 1, JPEG_QUALITY, pres->c_handler() );
#else
					onion_png_response( image, 4, 1, 1, pres->c_handler() );
#endif
					m_png_mutex.unlock();
					m_png_redraw = false;
					return 0;
				}

				if( scale == 100 ){
					/* copy pixels and generate file for this subimage */
					unsigned char image[channels*roi.width*roi.height];
					Mat pngRoi(*png,roi);

					if( channels == 4 ){
						/* Four channel image  */
						unsigned char *dst_it = image;
						MatConstIterator_<VT> it = pngRoi.begin<VT>(),
							it_end = pngRoi.end<VT>();
						for( ; it != it_end; ++it, ++dst_it ) {
							const VT pix = *it;
							//bgr => rgba	
							*dst_it = pix[2];
							++dst_it;
							*dst_it = pix[1];
							++dst_it;
							*dst_it = pix[0];
							++dst_it;
							*dst_it = 255;
						}
					}else{
						/* Grayscale image  */
						MatConstIterator_<uchar> it = pngRoi.begin<uchar>();
						const MatConstIterator_<uchar> it_end = pngRoi.end<uchar>();
						unsigned char *dst_it = image;
						for( ; it != it_end; ++it, ++dst_it ) { 
							*dst_it = *it; 
						}

					}
#ifdef WEB_DISPLAY_USES_JPEG
							onion_jpeg_response( (unsigned char*) image , channels, channels==1?JCS_GRAYSCALE:JCS_EXT_RGBX, roi.width, roi.height, JPEG_QUALITY, pres->c_handler() );
#else
							onion_png_response( (unsigned char*) image , channels, roi.width, roi.height, pres->c_handler() );
#endif

					VPRINT("image with dimensions %ix%i and %i channels sended.\n", roi.width, roi.height, channels);
				}else{
							/* Same as above but copy subset of all pixel */
							roi.width = (roi.width/4)*4;
							roi.height = (roi.height/4)*4;
							Mat pngRoi(*png,roi);
							//rescale to 50% or 25%				
							int w2 = roi.width*scale/100;
							int h2 = roi.height*scale/100;
							uint8_t incW = roi.width/w2;
							uint8_t incH = incW;//roi.height/h2;

							unsigned char image[channels*w2*h2];

							if( channels == 4 ){
								MatConstIterator_<VT> it = pngRoi.begin<VT>();
								uint8_t *pimage = (uint8_t*) image;
								uint8_t *nextRowImage = pimage + w2 * 4;
								for( int i=0 ; i<h2; ++i ){
									for( ; pimage<nextRowImage; ++pimage, it+=incW ){
										const	VT pix = *it;
										*pimage = pix[2];
										++pimage;
										*pimage = pix[1];
										++pimage;
										*pimage = pix[0];
										++pimage;
										*pimage = 255;
									}
									nextRowImage += w2 * 4;
									it+=roi.width*(incH-1);
								}
							}else{
								//uint32_t *pdata = (uint32_t*) data_ptr;//4*char, ARGB
								MatConstIterator_<uchar> it = pngRoi.begin<uchar>();

								uint8_t *pimage = (uint8_t*) image;
								uint8_t *nextRowImage = pimage + w2;
								for( int i=0 ; i<h2; ++i ){
									for( ; pimage<nextRowImage; ++pimage, it+=incW ){
										*pimage = *it;
									}
									nextRowImage += w2;
									it+=roi.width*(incH-1);
								}
							}

#ifdef WEB_DISPLAY_USES_JPEG
							onion_jpeg_response( (unsigned char*) image , channels, channels==1?JCS_GRAYSCALE:JCS_EXT_RGBX, w2, h2, JPEG_QUALITY, pres->c_handler() );
#else
							onion_png_response( (unsigned char*) image , channels, w2, h2, pres->c_handler() );
#endif
							VPRINT("image with dimensions %ix%i sended.\n", w2, h2);
						}

						m_png_mutex.unlock();
						m_png_redraw = false;
						m_png_scale  = scale;

						return 0;
					}
			break;
		default:
			break;
	}

	return -3;
}
