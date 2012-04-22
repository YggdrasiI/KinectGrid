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
  m_areaCol_ok(false),
	m_area_detection_step(0),
	m_pdevice(pdevice),
	m_depthMaskCounter(-NMASKFRAMES)//use -depthMaskCounter Frames as mask
{
	m_depthMask = Scalar(255);//temporary full mask
	m_areaMask = Scalar(0);
	m_parea_detection_mask = NULL;
	/*	_____ _____
	 *  |   | | 2 |
	 *  | 1 | |———|
	 *  |___||_20_|
	 */
	m_areaMask(Rect(30,30,KRES_X/2-60,KRES_Y-60)) = Scalar(1);
	m_areaMask(Rect(KRES_X/2+30,30,KRES_X/2-60,KRES_Y/2-30)) = Scalar(2);
	m_areaMask(Rect(KRES_X/2+30,KRES_Y/2-30,KRES_X/2-60,KRES_Y/2-30)) = Scalar(20);

	/* for(int i=0; i<16; i++)
		 for(int j=0; j<12; j++){
		 m_areaMask( Rect(i*40,j*40,40,40 )) = Scalar(i>8?200:10);
		 } */

}

ImageAnalysis::~ImageAnalysis()
{
	if( m_parea_detection_mask != NULL){
		cvReleaseImage(&m_parea_detection_mask);
		m_parea_detection_mask = NULL;
	}
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
}

FunctionMode ImageAnalysis::area_detection(Tracker *tracker)
{
	switch (m_area_detection_step) {
	case 2:
		{// Wait util no blob is detected.
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
			//2pixel wider and taller for floodfill
			if( m_parea_detection_mask == NULL){
				m_parea_detection_mask = cvCreateImage( cvSize(KRES_X+2,KRES_Y+2), IPL_DEPTH_8U, 1 );
			}else{
				cvSet(m_parea_detection_mask,cvScalar(0));
			}
//			m_area_detection_mask = Mat(m_areaMask.size().width+2,m_areaMask.size().height+2);
//
			//reset area mask and set full roi to one big area
			m_areaMask = Scalar(0);
			/* Set value in Roi to MAXAREAS+1 because Tracker ignore blobs in area=0 */
			m_areaMask(m_pSettingKinect->m_roi) = Scalar(MAXAREAS+1);
			
			m_area_detection_areas.clear();
		}
	case 1:
	default:
		{
			//Mat& depth = m_depthMaskWithoutThresh;
			tracker->trackBlobs(m_filteredMat(m_pSettingKinect->m_roi), m_areaMask, true);
			std::vector<cBlob>& blobs = tracker->getBlobs();
			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].areaid == 1 ){
					//detection finshed.
					m_area_detection_step = 0;
					m_pSettingKinect->m_areas = m_area_detection_areas;//copy mat

					//clear tmp IplImage
					if( m_parea_detection_mask != NULL){
						cvReleaseImage(&m_parea_detection_mask);
						m_parea_detection_mask = NULL;
					}

					return HAND_DETECTION;
				}
			}
			for(int i=0;i<blobs.size(); i++){
				if( blobs[i].areaid == MAXAREAS+1 ){
					//found new blob without area

					/* Flood fill of (old) depth image to detect area. use m_parea_detection_mask as mask
					 * to avoid overlapping of areas. Flag CV_FLOODFILL_MASK_ONLY is set to avoid changes
					 * in m_depthMask.
					 */
					CvMat foo = m_depthMask;//memory leak? No, it's no pointer.
					CvConnectedComp cc;
					cvFloodFill( &foo, cvPoint(blobs[i].location.x,blobs[i].location.y) , Scalar(255),
							Scalar(20), Scalar(4), &cc, 4+CV_FLOODFILL_MASK_ONLY, m_parea_detection_mask );

					if( cc.area < 400 ){
						printf("Area to small.\n");
						return AREA_DETECTION;
					}

					int areaid = m_area_detection_areas.size()+1;
					Area area;
					area.dim = cc.rect;
					area.id = areaid;
					area.color = Scalar( AREACOLORS[areaid%10][0], AREACOLORS[areaid%10][1], AREACOLORS[areaid%10][2]);
					area.area = cc.area;

					Mat tmp_mask = m_parea_detection_mask;//create mat header
					Mat changes = (m_areaMask(cc.rect)==MAXAREAS+1);//cut of other areas

					//get new !=0 values of m_parea_detection_mask
					changes.mul( tmp_mask(
								Rect(cc.rect.x+1,cc.rect.y+1,cc.rect.width,cc.rect.height)//shift by (1,1)
								) );

					changes *= areaid;
					changes.copyTo( m_areaMask, changes );

					m_area_detection_areas.push_back(area);

					tmp_mask.release();
					m_area_detection_step = 2;
					break;
				}
			}
		}break;
	}

	return AREA_DETECTION;
}

//++++++++

void ImageAnalysis::genColoredAreas(){
	m_areaCol = Scalar(0,0,0);
	Mat col(Size(640,480),CV_8UC3);
	int r,g,b;

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

	//CvScalar color = CV_RGB(250,0,0);
	//	cvFloodFill( out, seed_point, color, cvScalarAll(5.0), cvScalarAll(5.0), NULL, 4, NULL );

Mat ImageAnalysis::getColoredAreas(){
	if( !m_areaCol_ok ) genColoredAreas();

	Mat ret(Size(640,480),CV_8UC3);

	IplImage gray = m_depthf;
	IplImage rgb = ret;
	cvMerge(&gray, &gray, &gray, NULL, &rgb);
	addWeighted(ret,0.5f,m_areaCol,0.5f,0,ret);
	return ret;
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
	if( changes & MARGIN ){
		printf("ImageAnalysis: Change thresh val\n");
			addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_marginBack, m_depthMask);
	}
}
