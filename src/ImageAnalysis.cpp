#include "ImageAnalysis.h"

ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice, SettingKinect* pSettingKinect):
	m_pSettingKinect(pSettingKinect),
//	m_depthMat(Size(640,480),CV_16UC1),
	m_depthf  (Size(640,480),CV_8UC1),
	m_filterMat  (Size(640,480),CV_8UC1),
	m_depthMask  (Size(640,480),CV_8UC1),
	m_depthMaskWithoutThresh  (Size(640,480),CV_8UC1),//backup to generate new deptMask
	m_filteredMat  (Size(640,480),CV_8UC1),
	m_pdevice(pdevice),
	m_depthMaskCounter(-NMASKFRAMES)//use -depthMaskCounter Frames as mask
{
		m_depthMask = Scalar(255);//temporary full mask
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
