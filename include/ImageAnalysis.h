#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <vector>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "SettingKinect.h"

class ImageAnalysis{
public:
	ImageAnalysis(MyFreenectDevice* device, SettingKinect* pSettingKinect);
	~ImageAnalysis();
	void analyse();
	void hand_detection();
	void resetMask(SettingKinect* pSettingKinect, int changes);
	void genColoredAreas();
	Mat getColoredAreas();
public:
	Mat m_depthf  ;
	Mat m_filterMat;
	Mat m_depthMask;
	Mat m_depthMaskWithoutThresh;
	Mat m_filteredMat;
	Mat m_areaMask;
	Mat m_areaCol;//colored representation.
	bool m_areaCol_ok;
private:
	MyFreenectDevice* m_pdevice;
	SettingKinect* m_pSettingKinect;
	int m_depthMaskCounter;//use -depthMaskCounter Frames for mask generation
};

#endif
