#include <assert.h>
#include "ImageAnalysis.h"

ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice, SettingKinect* pSettingKinect):
	m_pSettingKinect(pSettingKinect),
//	m_depthMat(Size(KRES_X,KRES_Y),CV_16UC1),
	m_depthf  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_filterMat  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_depthMask  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_depthMaskWithoutThresh  (Size(KRES_X,KRES_Y),CV_8UC1),//backup to generate new deptMask
	m_filteredMat  (Size(KRES_X,KRES_Y),CV_8UC1),
	m_areaMask  (Size(KRES_X,KRES_Y),CV_8UC1), //mask of areas, ids=0,1,..., offcut=255
//	m_areaCol  (Size(KRES_X,KRES_Y),CV_8UC3),
	m_areaGrid  (Size(KRES_X,KRES_Y),CV_8UC1), //binary image of obstacles
	m_area_detection_mask  (Size(KRES_X+2,KRES_Y+2),CV_8UC1),
  m_areaCol_ok(false),
	m_area_detection_step(0),
	m_pdevice(pdevice),
	m_depthMaskCounter(-NMASKFRAMES)//use -depthMaskCounter Frames as mask
{
	m_depthMask = Scalar(255);//temporary full mask
	m_areaMask = Scalar(0);
	m_areaGrid = Scalar(255);
	/*	_____ _____
	 *  |   | | 2 |
	 *  | 1 | |———|
	 *  |___||_20_|
	 */
	//Rect a1 = Rect(30,30,KRES_X/2-60,KRES_Y-60);
	Rect a1 = Rect(200,100,300,200);
	int areaid = 1;
	m_areaMask(a1) = Scalar(areaid);
	//m_areaMask(Rect(KRES_X/2+30,30,KRES_X/2-60,KRES_Y/2-30)) = Scalar(2);
	//m_areaMask(Rect(KRES_X/2+30,KRES_Y/2-30,KRES_X/2-60,KRES_Y/2-30)) = Scalar(20);

	/* for(int i=0; i<16; i++)
		 for(int j=0; j<12; j++){
		 m_areaMask( Rect(i*40,j*40,40,40 )) = Scalar(i>8?200:10);
		 } */

	Area area;
	area.rect = a1;
	area.id = areaid;
	area.color = Scalar( AREACOLORS[areaid%10][0], AREACOLORS[areaid%10][1], AREACOLORS[areaid%10][2]);
	area.area = a1.width*a1.height;
	m_area_detection_areas.push_back(area);

	// set areas of Setting.
	m_pSettingKinect->m_areas = m_area_detection_areas;
}

ImageAnalysis::~ImageAnalysis()
{
}

FunctionMode ImageAnalysis::depth_mask_detection(){
	if( m_depthMaskCounter > 0){
		//depth mask already detected. Reset m_depthMaskCounter and begin again.
		m_depthMaskCounter = -NMASKFRAMES;
	}
	if( m_depthMaskCounter == -NMASKFRAMES ){
		m_depthMaskWithoutThresh = Scalar(0);
		m_depthMask = Scalar(255);//temporary full mask
	}
	if( m_depthMaskCounter < 0){
		// Use (fullsize) eary frames to generate mask
		m_pdevice->getDepth8UC1(m_depthf, Rect(0,0,KRES_X,KRES_Y));
		if( m_depthMaskCounter > 2-NMASKFRAMES)//depratecd error handling for first frames of device.
			createMask(m_depthf,m_depthMaskWithoutThresh,/*m_pSettingKinect->m_marginBack,*/m_depthMaskWithoutThresh);
		m_depthMaskCounter++;

		if( m_depthMaskCounter == 0 ){
			//last step
			addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_marginBack, m_depthMask);
			printf("Depth mask detection finished.\n");
			return HAND_DETECTION;
		}
		return DEPTH_MASK_DETECTION;
	}else{
		assert(false);
		return HAND_DETECTION;
	}
		return DEPTH_MASK_DETECTION;
}

FunctionMode ImageAnalysis::hand_detection()
{
//	printf("hand detection\n");
	if( m_depthMaskCounter < 0)
		return depth_mask_detection();

	Rect roi = m_pSettingKinect->m_roi;
	Mat dfRoi(m_depthf,roi);
	Mat dMRoi(m_depthMask,roi);
	Mat fMRoi(m_filteredMat,roi);

	// Analyse Roi of depth frame
	m_pdevice->getDepth8UC1(dfRoi, roi);

	//filter image
	filter(dfRoi,dMRoi,80,fMRoi);

	return HAND_DETECTION;
}

FunctionMode ImageAnalysis::area_detection(Tracker *tracker)
{
	switch (m_area_detection_step) {
	case 2:
		{// Wait util no blob is detected.
			printf("area detection 2\n");
			hand_detection();
			tracker->trackBlobs(m_filteredMat(m_pSettingKinect->m_roi), m_areaMask, true);
			if( tracker->getBlobs().size() == 0 ){
				m_area_detection_step = 1;
			}
		} break;
	case 3:
		{
		} break;
	case 0:
		{
			printf("area detection 0\n");

			// generate binary image for area detection
			genFrontMask();

			//2pixel wider and taller for floodfill
			m_area_detection_mask = Scalar(0);
			//reset area mask and set full roi to one big area
			m_areaMask = Scalar(0);
			/* Set value in Roi to MAXAREAS+1. (Tracker ignore blobs in area=0) */
			m_areaMask(m_pSettingKinect->m_roi) = Scalar(MAXAREAS+1);
			m_area_detection_areas.clear();

			genColoredAreas();
			m_area_detection_step = 1;
		}//no break!
	case 1:
	default:
		{
			printf("area detection 1\n");
			//Mat& depth = m_depthMaskWithoutThresh;
			hand_detection();
			tracker->trackBlobs(m_filteredMat(m_pSettingKinect->m_roi), m_areaMask, true);
			std::vector<cBlob>& blobs = tracker->getBlobs();

			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].event != BLOB_MOVE) continue;
				if( blobs[i].areaid == 1 ){
					/* detection finshed. */
					m_area_detection_step = 0;

					//reset pixels with MAXAREAS+1 value
					printf("Reset!!");
					threshold(m_areaMask, m_areaMask,MAXAREAS,0,THRESH_TOZERO_INV);

					m_pSettingKinect->m_areas = m_area_detection_areas;//copy vector 

					genColoredAreas();
					//clear blobs to begin fresh in hand detection.
					blobs.clear();
					return HAND_DETECTION;
				}
			}
			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].event != BLOB_MOVE) continue;
				if( blobs[i].areaid == MAXAREAS+1 ){
					//found new blob without area
					/* Flood fill of (old) depth image to detect area. use m_area_detection_mask as mask
					 * to avoid overlapping of areas. Flag CV_FLOODFILL_MASK_ONLY is set to avoid changes
					 * in m_depthMask.
					 * TODO: Looping of FloodFill with different low-high-values can improve results.
					 * TODO: Limit floodFill to Roi.
					 */
					Rect cc;
					floodFill(m_areaGrid/*m_depthMask*/, m_area_detection_mask, cvPoint(
								blobs[i].location.x+m_pSettingKinect->m_roi.x,
								blobs[i].location.y+m_pSettingKinect->m_roi.y ),
							Scalar(255), &cc, Scalar(/*20*/0)/*low*/, Scalar(0/*2*/)/*up*/, 4+FLOODFILL_MASK_ONLY);
				
					if( cc.width*cc.height < 800 ){
						printf("Area %i to small.\n", cc.width*cc.height);
						return AREA_DETECTION;
					}
					if( cc.width > 0.95*m_pSettingKinect->m_roi.width
							&& cc.height > 0.95*m_pSettingKinect->m_roi.height ){
						printf("Area %i very big and ignored. Depth mask ok?\n", cc.width*cc.height);
						return AREA_DETECTION;
					}

					int areaid = m_area_detection_areas.size()+1;
					printf("Create Area %i\n",areaid);
					Area area;
					area.rect = cc;
					area.id = areaid;
					area.color = Scalar( AREACOLORS[areaid%10][0], AREACOLORS[areaid%10][1], AREACOLORS[areaid%10][2]);
					area.area = cc.width*cc.height;

					Mat changeable = (m_areaMask(cc)==MAXAREAS+1);//cut of other areas

					//get new !=0 values of m_area_detection_mask
					changeable = min(changeable, m_area_detection_mask(
								Rect(cc.x+1,cc.y+1,cc.width,cc.height)//shift by (1,1)
								 ));

					changeable *= areaid;
					Mat areaMaskDst = m_areaMask(cc);
					changeable.copyTo( areaMaskDst, changeable );
//m_areaMask(cc ) = Scalar(areaid);

					cv::imshow("img", (m_area_detection_mask*100)(m_pSettingKinect->m_roi) );
					cvWaitKey(1000);
					//update m_areaCol 
					genColoredAreas();

					m_area_detection_areas.push_back(area);

					m_area_detection_step = 2;
					break;
				}
			}
		}break;
	}

	return AREA_DETECTION;
}

//++++++++

void ImageAnalysis::genFrontMask(){
	m_areaGrid = Scalar(255);
	Rect roi = m_pSettingKinect->m_roi;
	Mat agRoi(m_areaGrid,roi);
//	Mat newAreaGrid = Mat(Size(roi.width,roi.height), CV_8UC1);

	m_pdevice->getDepth8UC1(agRoi, roi);
	Mat Kernel(Size(3, 3), CV_8UC1); Kernel.setTo(Scalar(1));
	dilate(agRoi, agRoi, Kernel); 
	threshold(agRoi, agRoi,255-m_pSettingKinect->m_marginFront,255,THRESH_BINARY);
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


Mat ImageAnalysis::getColoredAreas(){
	if( !m_areaCol_ok ) genColoredAreas();

	Mat ret(Size(640,480),CV_8UC3);

	IplImage gray = m_depthf;
	IplImage rgb = ret;
	cvMerge(&gray, &gray, &gray, NULL, &rgb);
	addWeighted(ret,0.5f,m_areaCol,0.5f,0,ret);
	return ret;
}

Mat ImageAnalysis::getFrontMask(){
	if( !m_maskFront_ok ) genFrontMask();
	return m_areaGrid;
}
/*
 * Reset internal counter of mask detection and clear mask.
 * New mask will generated.
 */
void ImageAnalysis::resetMask(SettingKinect* pSettingKinect, int changes){
	if( changes & (MASK|MOTOR|CONFIG) ){
		printf("ImageAnalysis: Create new mask\n");
		m_depthMaskWithoutThresh = Scalar(0);
		m_depthMask = Scalar(255);//temporary full mask
		m_depthMaskCounter = -NMASKFRAMES;

	}
	if( changes & FRONT_MASK ){
		m_maskFront_ok = false;
	}
	if( changes & MARGIN ){
		printf("ImageAnalysis: Change thresh val\n");
			addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_marginBack, m_depthMask);
	}
}
