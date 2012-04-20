#include "ImageAnalysis.h"

ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice, SettingKinect* pSettingKinect):
	m_pSettingKinect(pSettingKinect),
//	m_depthMat(Size(640,480),CV_16UC1),
	m_depthf  (Size(640,480),CV_8UC1),
	m_filterMat  (Size(640,480),CV_8UC1),
	m_depthMask  (Size(640,480),CV_8UC1),
	m_depthMaskWithoutThresh  (Size(640,480),CV_8UC1),//backup to generate new deptMask
	m_filteredMat  (Size(640,480),CV_8UC1),
	m_areaMask  (Size(640,480),CV_8UC1), //mask of areas, ids=0,1,..., offcut=255
//	m_areaCol  (Size(640,480),CV_8UC3),
  m_areaCol_ok(false),
	m_pdevice(pdevice),
	m_depthMaskCounter(-NMASKFRAMES)//use -depthMaskCounter Frames as mask
{
		m_depthMask = Scalar(255);//temporary full mask
		m_areaMask = Scalar(0);
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
}

void ImageAnalysis::analyse()
{
	Rect roi = m_pSettingKinect->m_roi;
	Mat dfRoi(m_depthf,roi);
	Mat dMRoi(m_depthMask,roi);
	Mat fMRoi(m_filteredMat,roi);

	if( m_depthMaskCounter < 0){
		// Use (fullsize) eary frames to generate mask
		m_pdevice->getDepth8UC1(m_depthf, Rect(0,0,KRES_X,KRES_Y));
		if( m_depthMaskCounter++ > 5-NMASKFRAMES)
			createMask(m_depthf,m_depthMaskWithoutThresh,/*m_pSettingKinect->m_marginBack,*/m_depthMaskWithoutThresh);
		if( m_depthMaskCounter == 0)
			addThresh(m_depthMaskWithoutThresh, m_pSettingKinect->m_marginBack, m_depthMask);
	}else{
		// Analyse Roi of depth frame
		m_pdevice->getDepth8UC1(dfRoi, roi);
	}

	//filter image
	filter(dfRoi,dMRoi,80,fMRoi);
}

void ImageAnalysis::hand_detection()
{


}

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
