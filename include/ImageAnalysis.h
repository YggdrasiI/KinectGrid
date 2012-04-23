#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <vector>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "SettingKinect.h"
#include "Tracker.h"
#include "blob.h"
#include "Mutex.h"

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
	void genFrontMask();
	void genColoredAreas();
	Mat getColoredAreas();
	Mat getFrontMask();
public:
	Mat m_depthf  ;
	Mat m_filterMat;
	Mat m_depthMask;
	Mat m_depthMaskWithoutThresh;
	Mat m_filteredMat;
	Mat m_areaMask;
	Mat m_areaGrid;
	Mat m_areaCol;//colored representation.
	bool m_areaCol_ok;
	bool m_maskFront_ok;
	int m_area_detection_step;
private:
	MyFreenectDevice* m_pdevice;
	SettingKinect* m_pSettingKinect;
	int m_depthMaskCounter;//use -depthMaskCounter Frames for mask generation
	Mat m_area_detection_mask;
	std::vector<Area> m_area_detection_areas;
};




/******** some usefull opencv based functions. *********/

/*
 * 
 */
inline void addThresh(Mat& src, int nthresh, Mat& dst){
	dst = max(src,nthresh);
}

static void createMask(Mat& src, Mat& oldMask,/* int nthresh,*/ Mat& mask){

	//Increase dark (near) parts to filter contur errors.
	Mat Kernel(Size(3, 3), CV_8UC1);
	Kernel.setTo(Scalar(1));
	dilate(src, mask, Kernel); 
	dilate(mask, mask, Kernel); 
	//dilate(mask, mask, Kernel); 

	/*Mat threshold(src.size(), src.type());
	threshold.setTo(Scalar(nthresh));
	mask = max(mask,threshold);*/
	//mask = max(mask+4,nthresh);

	//shift mask to filter small distance errors.
	mask = max(mask+4,oldMask);
}

//dst will used as tmp val
static void filter(Mat& src, Mat& mask, int nthresh, Mat& dst){
	Mat tmp(src.size(), src.type());
	blur(src, tmp, Size(3,3));

	dst = mask < tmp ;
	tmp.copyTo(dst, dst);
	/* this threshold can be integrated in the above mask.
	 * Disadvantage: No adaptive change of this barier possible...
	//threshold(dst, dst, nthresh, 255, THRESH_BINARY);
	threshold(dst, dst, nthresh, 255, THRESH_TOZERO);
	//adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, nthresh);
	*/
}


#endif
