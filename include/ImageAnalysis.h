#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

#include <vector>
#include <onion/onion.hpp>
#include <onion/response.hpp>

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
		Mat m_depthf  ;
		Mat m_filterMat;
		Mat m_depthMask;
		Mat m_depthMaskWithoutThresh;
		Mat m_depthMask16U;
		Mat m_filteredMat;
		Mat m_areaMask;
		Mat m_areaGrid;
		Mat m_areaCol;//colored representation.
		Mat m_rgb; //tmp var for rgb images ret(Size(640,480),CV_8UC3);
		bool m_areaCol_ok;
		bool m_maskFront_ok;
		int m_area_detection_step;
		bool m_png_redraw; //mark if png_redraw is useful.
		::Mutex m_png_mutex;
		int m_png_scale; //mark last scale factor of png.
	private:
		Mat m_area_detection_mask;
		MyFreenectDevice* m_pdevice;
		SettingKinect* m_pSettingKinect;
		int m_depthMaskCounter;//use -depthMaskCounter Frames for mask generation
		std::vector<Area> m_area_detection_areas;
		Mat m_png_imgC1;
		Mat m_png_imgC3;
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
		Mat &getFrontMask();
		void finishDepthMaskCreation();
		bool getDisplayedImage(Onion::Request *preq, int actionid, Onion::Response *pres);
	private:
		void repoke_init();
		bool repoke_step(Area& area);
		void repoke_finish();
		void addAreaThresh(/*Mat& src,*/ std::vector<Area> areas, Mat& areaMask,  Mat& dst);
};




/******** some useful opencv based functions. *********/

/*
 * 
 */
inline void addThresh(Mat& src, int nthresh, Mat& dst){
	dst = max(src,nthresh);
}

static void createMask(Mat& src, Mat& oldMask,/* int nthresh,*/ Mat& mask){

	//Increase dark (near) parts to filter contour errors.
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

	dst = mask < tmp ;//0-1-image
	tmp.copyTo(dst, dst);// 0-'blob-depth'-image
	
}

/* Output black/white  */
static void filterBW(Mat& src, Mat& mask, int nthresh, Mat& dst){
	Mat tmp(src.size(), src.type());
	blur(src, tmp, Size(3,3));

	dst = mask < tmp ;//0-1-image
}

//no blur test
static void filterNoBlur(Mat& src, Mat& mask, int nthresh, Mat& dst){
	Mat tmp(src.size(), src.type());
	dst = mask < tmp ;//0-1-image
	src.copyTo(dst, dst);// 0-'blob-depth'-image
}

static void filterBWNoBlur(Mat& src, Mat& mask, int nthresh, Mat& dst){
	Mat tmp(src.size(), src.type());
	dst = mask < tmp ;//0-1-image
}

#endif
