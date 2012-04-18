#ifndef MyFreenectDevice_H
#define MyFreenectDevice_H

#include "libfreenect.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <cv.h>
#include <cxcore.h>
//#include <highgui.h>

#include "Mutex.h"
#include "BlobResult.h"

#include "SettingKinect.h"

using namespace cv;
using namespace std;


class MyFreenectDevice : public Freenect::FreenectDevice {
  public:
	MyFreenectDevice(freenect_context *_ctx, int _index);
	~MyFreenectDevice();

	// Do not call directly even in child
	void VideoCallback(void* _rgb, uint32_t timestamp);
	// Do not call directly even in child
	void DepthCallback(void* _depth, uint32_t timestamp); 
	bool getVideo(Mat& output); 
	bool getDepth(Mat& output);
/*
 Convert depth direct to U8C1 to avoid copy and convert later.
*/
	bool getDepth8UC1(Mat& output, Rect roi); 
//	void setSettingKinect(SettingKinect* sk);

	/* propagate setting changes */
	void update(SettingKinect* pSettingKinect, int changes);

  private:
	std::vector<uint8_t> m_buffer_depth;
	std::vector<uint8_t> m_buffer_rgb;
	std::vector<uint16_t> m_gamma;
	Mat m_depthMat;
	Mat m_rgbMat;
	Mutex m_rgb_mutex;
	Mutex m_depth_mutex;
	bool m_new_rgb_frame;
	bool m_new_depth_frame;
	//SettingKinect* m_pSettingKinect;
};


/******** some usefull opencv based functions. *********/

/*
 * 
 */
static void createMask(Mat& src, Mat& oldMask, int nthresh, Mat& mask){

	//Increase dark (near) parts to filter contur errors.
	Mat Kernel(Size(5, 5), CV_8UC1);
	Kernel.setTo(Scalar(1));
	dilate(src, mask, Kernel); 
	dilate(mask, mask, Kernel); 
	dilate(mask, mask, Kernel); 

	/*Mat threshold(src.size(), src.type());
	threshold.setTo(Scalar(nthresh));
	mask = max(mask,threshold);*/
	mask = max(mask+4,nthresh);

	//shift mask to filter small distance errors.
	mask = max(mask,oldMask);
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
