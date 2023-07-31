#ifndef MyFreenectDevice_H
#define MyFreenectDevice_H

#include "libfreenect.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "Mutex.h"
#include "BlobResult.h"

#include "SettingKinect.h"

//using namespace cv;
using namespace std;


class MyFreenectDevice : public Freenect::FreenectDevice {
  public:
	MyFreenectDevice(freenect_context *_ctx, int _index);
	~MyFreenectDevice();

	// Do not call directly even in child
	void VideoCallback(void* _rgb, uint32_t timestamp);
	// Do not call directly even in child
	void DepthCallback(void* _depth, uint32_t timestamp); 
	bool getVideo(cv::Mat& output); 
	bool getDepth(cv::Mat& output);
/*
 Convert depth direct to U8C1 to avoid copy and convert later.
*/
	bool getDepth8UC1(cv::Mat& output, cv::Rect roi); 
	bool getDepth8UC1(cv::Mat& output, cv::Rect roi, int m, int M); 
	bool getDepth8UC1(cv::Mat& output, cv::Rect roi, int m, int M, cv::Mat& mask); 
	bool getDepth8UC1_b(cv::Mat& output, cv::Rect roi, int m, int M, cv::Mat& mask); 
	bool getDepth8UC1_b(cv::Mat& dst, cv::Rect roi, uint8_t *map, cv::Mat& mask);

	/* propagate setting changes */
	void update(SettingKinect* pSettingKinect, int changes);

	/* Enable clipping in libfreenect driver */
	int setRoi(bool enable,const cv::Rect roi){
#ifdef LIBFREENECT_OPT_CLIPPING 
		int top = roi.y;
		int bottom = KRES_Y - roi.height - roi.y ;
		int left = roi.x;
		int right = KRES_X - roi.width - roi.x ;
		return setClipping(enable, top, bottom, left, right);
#else
		printf("[MyFreenectDevice] setClipping not available\n");
		return 0;
#endif
	};

  private:
	std::vector<uint8_t> m_buffer_depth;
	std::vector<uint8_t> m_buffer_rgb;
//	std::vector<uint16_t> m_gamma;
	cv::Mat m_depthMat;
	cv::Mat m_rgbMat;
	::Mutex m_rgb_mutex;
	::Mutex m_depth_mutex;
	bool m_new_rgb_frame;
	bool m_new_depth_frame;
	//SettingKinect* m_pSettingKinect;
};



#endif
