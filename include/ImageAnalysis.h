#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <vector>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "SettingKinect.h"
#include "Tracker.h"
#include "blob.h"

// used in area detection.
#define CV_FLOODFILL_MASK_ONLY   (1 << 17)


class ImageAnalysis{
public:
	ImageAnalysis(MyFreenectDevice* device, SettingKinect* pSettingKinect);
	~ImageAnalysis();
	FunctionMode depth_mask_detection();
	FunctionMode hand_detection();
	FunctionMode area_detection(Tracker *tracker);

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
	int m_area_detection_step;
	IplImage *m_parea_detection_mask;
	std::vector<Area> m_area_detection_areas;
};

#endif
