#include "MyFreenectDevice.h"


MyFreenectDevice::MyFreenectDevice(freenect_context *_ctx, int _index):
	Freenect::FreenectDevice(_ctx, _index),
	m_buffer_depth(FREENECT_DEPTH_11BIT),
	m_buffer_rgb(FREENECT_VIDEO_RGB),
	m_gamma(2048),
	m_new_rgb_frame(false),
	m_new_depth_frame(false),
	m_depthMat(Size(640,480),CV_16UC1),
	m_rgbMat(Size(640,480),CV_8UC3,Scalar(0))
{


	for( unsigned int i = 0 ; i < 2048 ; i++) {
		float v = i/2048.0;
		v = std::pow(v, 3)* 6;
		m_gamma[i] = v*6*256;
	}
}

MyFreenectDevice::~MyFreenectDevice()
{
	stopDepth();
	//freenect.deleteDevice(0); 
}

	// Do not call directly even in child
void MyFreenectDevice::VideoCallback(void* _rgb, uint32_t timestamp)
{
	std::cout << "RGB callback" << std::endl;
	m_rgb_mutex.lock();
	uint8_t* rgb = static_cast<uint8_t*>(_rgb);
	m_rgbMat.data = rgb;
	m_new_rgb_frame = true;
	m_rgb_mutex.unlock();
}

	// Do not call directly even in child
void MyFreenectDevice::DepthCallback(void* _depth, uint32_t timestamp)
{
	//std::cout << "Depth callback" << std::endl;
	m_depth_mutex.lock();
	uint16_t* depth = static_cast<uint16_t*>(_depth);
	m_depthMat.data = (uchar*) depth;
	m_new_depth_frame = true;
	m_depth_mutex.unlock();
}

bool MyFreenectDevice::getVideo(Mat& output)
{
	m_rgb_mutex.lock();
	if(m_new_rgb_frame) {
		cv::cvtColor(m_rgbMat, output, CV_RGB2BGR);
		m_new_rgb_frame = false;
		m_rgb_mutex.unlock();
		return true;
	} else {
		m_rgb_mutex.unlock();
		return false;
	}
}

/*
 Convert depth to U8C1 to avoid copy and convert later.
*/
bool MyFreenectDevice::getDepth8UC1(Mat& output, Rect roi) 
{
	m_depth_mutex.lock();
	if(m_new_depth_frame) {
		//printf("Dim of roiMat: %i %i\n", output.size().width, output.size().height);
		//m_depthMat.convertTo(output, CV_8UC1, -255.0/2048.0, 255.0);//Invert colors!
		m_depthMat(roi).convertTo(output, CV_8UC1, -255.0/2048.0, 255.0);//Invert colors!
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		m_depth_mutex.unlock();
		return false;
	}
}


bool MyFreenectDevice::getDepth(Mat& output)
{
	m_depth_mutex.lock();
	if(m_new_depth_frame) {
		m_depthMat.copyTo(output);
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		m_depth_mutex.unlock();
		return false;
	}
}

/*void MyFreenectDevice::setSettingKinect(SettingKinect* sk){
	if(sk==NULL) return;
	m_pSettingKinect=sk;
	m_pSettingKinect->setDevice(this);
	update();
}*/

void MyFreenectDevice::update(SettingKinect* pSettingKinect){
	// Set vertical Position
	setTiltDegrees(pSettingKinect->m_kinectMotorAngle);
	// Set Led of device
	setLed(LED_GREEN);
}

