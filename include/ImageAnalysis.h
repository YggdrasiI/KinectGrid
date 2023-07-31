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

/* Internal start for area detetion modes. */
enum areaDetectionStep {
	AREA_DETECTION_STEP_UNSET=-1,
	AREA_DETECTION_STEP_INIT=0,
	AREA_DETECTION_STEP_WAIT_BLOB,
	AREA_DETECTION_STEP_WAIT_VOID,
	AREA_DETECTION_STEP_FINISH,
	AREA_DETECTION_STEP_BY_CLICK, // Extra state for detection over frontent (web or x11).
};

class ImageAnalysis{
	public:
		cv::Mat m_depthf  ;
		cv::Mat m_filterMat;
		cv::Mat m_depthMask;
		cv::Mat m_depthMaskWithoutThresh;
		cv::Mat m_depthMask16U;
		cv::Mat m_filteredMat;
		cv::Mat m_areaMask;
		cv::Mat m_areaGrid;
		cv::Mat m_areaCol;//colored representation.
		cv::Mat m_rgb; //tmp var for rgb images ret(cv::Size(640,480),CV_8UC3);
		bool m_areaCol_ok;
		bool m_maskFront_ok;
		int m_area_detection_step;
		bool m_png_redraw; //mark if png_redraw is useful.
		::Mutex m_png_mutex;
		int m_png_scale; //mark last scale factor of png.
	private:
		cv::Mat m_area_detection_mask;
		MyFreenectDevice* m_pdevice;
		SettingKinect* m_pSettingKinect;
		int m_depthMaskCounter;//use -depthMaskCounter Frames for mask generation
		std::vector<Area> m_area_detection_areas;
		cv::Mat m_png_imgC1;
		cv::Mat m_png_imgC3;
	public:
		ImageAnalysis(MyFreenectDevice* device, SettingKinect* pSettingKinect);
		~ImageAnalysis();
		FunctionMode depth_mask_detection();
		FunctionMode hand_detection();
		FunctionMode area_detection(Tracker *tracker);

		void resetMask(SettingKinect* pSettingKinect, int changes);
		void genFrontMask();
		void genColoredAreas();
		cv::Mat &getColoredAreas();
		cv::Mat &getFrontMask();
		void finishDepthMaskCreation();
		// general signal handling of this object.
		int http_actions(Onion::Request *preq, int actionid, Onion::Response *pres);
		// extra signal for web display mode
		int getWebDisplayImage(Onion::Request *preq, int actionid, Onion::Response *pres);
		/* For area detection in OpenCV window.
		 * Return values:
		 *	-4 Unknown result/error
		 *	-3 Serer not in detection mode. Done nothing.
		 *	-2 Wrong input
		 *	-1 No area found for coordinates
		 *	 0 Server finished detection.
		 *	>0 Server found area and return it's id.
		 */
		int area_detection_opencv_click(int x, int y);
	private:
		void repoke_init();
		bool repoke_step(Area& area);
		void repoke_finish();
		void addAreaThresh(/*cv::Mat& src,*/ std::vector<Area> areas, cv::Mat& areaMask,  cv::Mat& dst);
};




/******** some useful opencv based functions. *********/

/*
 * 
 */
inline void addThresh(cv::Mat& src, int nthresh, cv::Mat& dst){
	dst = max(src,nthresh);
}

static void createMask(cv::Mat& src, cv::Mat& oldMask,/* int nthresh,*/ cv::Mat& mask){

	//Increase dark (near) parts to filter contour errors.
	cv::Mat Kernel(cv::Size(3, 3), CV_8UC1);
	Kernel.setTo(cv::Scalar(1));
	dilate(src, mask, Kernel); 
	dilate(mask, mask, Kernel); 
	//dilate(mask, mask, Kernel); 

	/*cv::Mat threshold(src.size(), src.type());
	threshold.setTo(cv::Scalar(nthresh));
	mask = max(mask,threshold);*/
	//mask = max(mask+4,nthresh);

	//shift mask to filter small distance errors.
	mask = max(mask+4,oldMask);
}

//dst will used as tmp val
static void filter(cv::Mat& src, cv::Mat& mask, int nthresh, cv::Mat& dst){
	cv::Mat tmp(src.size(), src.type());
	blur(src, tmp, cv::Size(3,3));

	dst = mask < tmp ;//0-1-image
	tmp.copyTo(dst, dst);// 0-'blob-depth'-image
	
}

/* Output black/white  */
static void filterBW(cv::Mat& src, cv::Mat& mask, int nthresh, cv::Mat& dst){
	cv::Mat tmp(src.size(), src.type());
	blur(src, tmp, cv::Size(3,3));

	dst = mask < tmp ;//0-1-image
}

//no blur test
static void filterNoBlur(cv::Mat& src, cv::Mat& mask, int nthresh, cv::Mat& dst){
	cv::Mat tmp(src.size(), src.type());
	dst = mask < tmp ;//0-1-image
	src.copyTo(dst, dst);// 0-'blob-depth'-image
}

static void filterBWNoBlur(cv::Mat& src, cv::Mat& mask, int nthresh, cv::Mat& dst){
	cv::Mat tmp(src.size(), src.type());
	dst = mask < tmp ;//0-1-image
}

#endif
