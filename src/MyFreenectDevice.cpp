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
	m_depth_mutex.lock();
	stopDepth();
	m_depth_mutex.unlock();
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
		//m_depthMat(roi).convertTo(output, CV_8UC1, -255.0/2048.0, 255.0);//Invert colors!
		m_depthMat(roi).convertTo(output, CV_8UC1, -255.0/1024.0, 255+127.0);//Invert colors!
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		m_depth_mutex.unlock();
		return false;
	}
}

/*
 Convert depth to U8C1 to avoid copy and convert later.
 Here, two affine functions are combined.
 • f(x) := a*x + b map the depth to [0,255] intervall,
    (a,b)=(255/2048,0) or (-255/2048,255).
 • g(y) := 255/(M-m) (y - m) map [m,M] on [0,255].
 => The depth resolution will increased in the relevant intervall.
*/
bool MyFreenectDevice::getDepth8UC1(Mat& output, Rect roi, int m, int M) 
{
	if(m_new_depth_frame) {
		float a2 = -255.0*255.0/2048.0/(M-m);	
		float b2 = (255.0-m)*255.0/(M-m);	
		//	printf("getDepth constants: %f, %f\n",a2,b2);
		m_depth_mutex.lock();
		m_depthMat(roi).convertTo(output, CV_8UC1, a2, b2);//Invert colors!
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		//m_depth_mutex.unlock();
		return false;
	}
}

/*
 Masked Version. (No blur!)
 mask.type = CV_8UC1.
*/
bool MyFreenectDevice::getDepth8UC1(Mat& dst, Rect roi, int m, int M, Mat& mask) 
{
	m_depth_mutex.lock();
	if(m_new_depth_frame) {
		float a = -255.0*255.0/2048.0/(M-m);	
		float b = (255.0-m)*255.0/(M-m);	
		//	printf("getDepth constants: %f, %f\n",a2,b2);

		Mat dRoi = m_depthMat(roi);
		MatConstIterator_<uint16_t> it1 = dRoi.begin<uint16_t>(),
			it1_end = dRoi.end<uint16_t>();
		MatConstIterator_<uchar> it2 = mask.begin<uchar>();
		MatIterator_<uchar> dst_it = dst.begin<uchar>();
		uchar tmp;
		for( ; it1 != it1_end; ++it1, ++it2, ++dst_it ) { 
			//previous memcopy for 99%-else case?!
			//tmp = a**it1+b;
			//*dst_it = (tmp>*it2)?tmp:0;

			*dst_it = a**it1+b;
			if(*dst_it<=*it2) *dst_it = 0;
		}
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		m_depth_mutex.unlock();
		return false;
	}
}
/*
 Masked Version. (No blur!)
 mask.type = CV_16UC1. (=> Switch if and multiplication)
*/
bool MyFreenectDevice::getDepth8UC1_b(Mat& dst, Rect roi, int m, int M, Mat& mask) 
{
	if(m_new_depth_frame) {
		m_depth_mutex.lock();
		//float a = -255.0*255.0/2048.0/(M-m);	
		//float b = (255.0-m)*255.0/(M-m);	
		//	printf("getDepth constants: %f, %f\n",a,b);
		int iaz, ian, ib;
		iaz = -255*255;
		ian = 2048*(M-m);
		ib = (255-m)*255/(M-m);

		Mat dRoi = m_depthMat(roi);
		MatConstIterator_<uint16_t> it1 = dRoi.begin<uint16_t>(),
			it1_end = dRoi.end<uint16_t>();
		MatConstIterator_<uint16_t> it2 = mask.begin<uint16_t>();
		MatIterator_<uchar> dst_it = dst.begin<uchar>();
		uchar tmp;
		//fill with zeros
		dst = Scalar(0);
		for( ; it1 != it1_end; ++it1, ++it2, ++dst_it ) { 
			//if( *it1<*it2 ) *dst_it = a* *it1 + b;
			if( *it1<*it2 ) *dst_it = (iaz* *it1)/ian + ib;
		}
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		//m_depth_mutex.unlock();
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

void MyFreenectDevice::update(SettingKinect* pSettingKinect, int changes){
	// Set vertical Position
	if( changes &  MOTOR ){
		printf("MyFreenectDevice: Set motor degree\n");
		setTiltDegrees(pSettingKinect->m_kinectMotorAngle);
	}
	// Set Led of device
	setLed(LED_GREEN);
}

