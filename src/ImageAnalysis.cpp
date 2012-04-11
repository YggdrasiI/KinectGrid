#include "ImageAnalysis.h"

ImageAnalysis::ImageAnalysis(MyFreenectDevice* pdevice):
	m_depthMat(Size(640,480),CV_16UC1),
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
	m_pdevice->getDepth8UC1(m_depthf);

	// Use eary frames to generate mask
	if( m_depthMaskCounter < 0){
		if( m_depthMaskCounter++ > -25) createMask(m_depthf,m_depthMask,80,m_depthMask);
	}

	//filter image
	filter(m_depthf,m_depthMask,80, m_filteredMat);
}
