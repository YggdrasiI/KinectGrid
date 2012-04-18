#include "ImageAnalysis.h"

ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice, SettingKinect* pSettingKinect):
	m_pSettingKinect(pSettingKinect),
//	m_depthMat(Size(640,480),CV_16UC1),
	m_depthf  (Size(640,480),CV_8UC1),
	m_filterMat  (Size(640,480),CV_8UC1),
	m_depthMask  (Size(640,480),CV_8UC1),
	m_filteredMat  (Size(640,480),CV_8UC1),
	m_pdevice(pdevice),
	m_depthMaskCounter(-30)//use -depthMaskCounter Frame as mask
{
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
		if( m_depthMaskCounter++ > -25) createMask(m_depthf,m_depthMask,80,m_depthMask);
	}else{
		// Analyse Roi of depth frame
		m_pdevice->getDepth8UC1(dfRoi, roi);
	}

	//filter image
	filter(dfRoi,dMRoi,80,fMRoi);
}
