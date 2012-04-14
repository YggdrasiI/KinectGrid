#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "ImageAnalysis.h"
#include "BlobResult.h"
#include "Tracker.h"
#include "JsonConfig.h"
#include "OnionServer.h"



int main(int argc, char **argv) {
	bool die(false);
  bool withKinect(false);
	string filename("snapshot");
	string suffix(".png");
	int iter(0);

	int nthresh = 140;
	if( argc > 1){
		nthresh = atoi(argv[1]);
		printf("Threshval: %i\n",nthresh);
	}

	//Load & Create settings
	//JsonConfig settingMMTT("settingMMTT.json", &JsonConfig::loadMMTTlinuxSetting  );
	JsonConfig *settingMMTT = new SettingMMTT("settingMMTT.json.x");
	
	if(true){
	char *conf = settingMMTT->getConfig();
	printf("Settings:%s \n", conf);
	free(conf);
	}
	//JsonConfig settingKinect("settingKinectDefault.json", &JsonConfig::loadKinectSetting );
	JsonConfig *settingKinect = new SettingKinect( settingMMTT->getString("lastSetting") );

	if(true){
	char *conf = settingKinect->getConfig();
	printf("Settings:%s \n", conf);
	free(conf);
	}


	//init onion server thread
	OnionServer* onion = new OnionServer(settingMMTT, settingKinect); 
	onion->start_server();

	ImageAnalysis* ia;
	//Freenect::Freenect freenect;
	//MyFreenectDevice& device = freenect.createDevice<MyFreenectDevice>(0); 
	Freenect::Freenect* freenect;
	MyFreenectDevice* device;
	Tracker tracker(TMINAREA, TMAXRADIUS);

	if(withKinect){
		freenect = new Freenect::Freenect;
		/* wie kann ich mir den umweg über mydevice sparen?!*/
		MyFreenectDevice& mydevice = freenect->createDevice<MyFreenectDevice>(0); 
		device = &mydevice;
		ia = new ImageAnalysis(device, settingKinect);

		// Set vertical Position
		device->setTiltDegrees(0.0);

		// Set Led of device
		device->setLed(LED_GREEN);

		//device.startVideo();
		device->startDepth();

		//namedWindow("rgb",CV_WINDOW_AUTOSIZE);
		namedWindow("depth",CV_WINDOW_AUTOSIZE);
		namedWindow("filter",CV_WINDOW_AUTOSIZE);
	}


	while (!die) {
		//device.getVideo(rgbMat);
		//cv::imshow("rgb", rgbMat);
		//device.getDepth(depthMat);

		//get 8 bit depth image
		if(withKinect){
			ia->analyse(); 
			//find blobs
			//tracker.trackBlobs(ia->m_filteredMat, true);
			/*
				 _tmpThresh->origin = 1;
				 _tmpThresh->imageData = (char*) depthf.data;
				 _newblobresult = new CBlobResult(_tmpThresh, NULL, 0, false);

				 _newblobresult->Filter( *_newblobresult, B_EXCLUDE, CBlobGetArea(), B_GREATER, val_blob_maxsize.internal_value );
				 _newblobresult->Filter( *_newblobresult, B_EXCLUDE, CBlobGetArea(), B_LESS, val_blob_minsize.internal_value );
				 */

			cv::imshow("depth",ia->m_depthf);
			cv::imshow("filter",ia->m_filteredMat);
		}else{
			sleep(1);
		}

		char k = cvWaitKey(5);
		if( k == 27 ){
			printf("End main loop\n");
			die = true;
			break;
		}
		if( k == 8 ) {
			/*
				 std::ostringstream file;
				 file << filename << i_snap << suffix;
				 cv::imwrite(file.str(),rgbMat);
				 i_snap++;
				 */
		}
		if(iter >= 20000) break;
		iter++;
	}

	/* Clean up objects */
	if(withKinect){
		//device.stopVideo();
		cvDestroyWindow("filter");
		cvDestroyWindow("depth");
		delete ia;
		delete freenect;
	}

	delete onion;
	delete settingKinect;
	delete settingMMTT;

	return 0;
}

