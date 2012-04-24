#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <boost/signal.hpp>
#include <boost/bind.hpp>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "ImageAnalysis.h"
#include "BlobResult.h"
#include "Tracker.h"
#include "JsonConfig.h"
#include "OnionServer.h"
#include "MyTuioServer.h"
#include "MyTuioServer25D.h"

// Selection of output image
enum Show {SHOW_DEPTH=1,SHOW_MASK=2,SHOW_FILTERED=3,SHOW_AREAS=4,SHOW_FRONTMASK};

int main(int argc, char **argv) {
	bool die(false);
  bool withKinect(true);
	int imshowNbr = SHOW_FILTERED; 
	string filename("snapshot");
	string suffix(".png");
	int iter(0);

	if( argc > 1){
		int wk = atoi(argv[1]);
		if(wk==0) withKinect=false;
	}

	//Load & Create settings
	//JsonConfig settingMMTT("settingMMTT.json", &JsonConfig::loadMMTTlinuxSetting  );
	SettingMMTT *settingMMTT = new SettingMMTT();
	settingMMTT->init("settingMMTT.ini");
	
	if(false){
	char *conf = settingMMTT->getConfig();
	printf("Settings:%s \n", conf);
	free(conf);
	}
	//JsonConfig settingKinect("settingKinectDefault.json", &JsonConfig::loadKinectSetting );
	SettingKinect *settingKinect = new SettingKinect();
	//settingKinect->init("settingKinectDefault.json");
	settingKinect->init( settingMMTT->getString("lastSetting") );

	if(false){
	char *conf = settingKinect->getConfig();
	printf("Settings:%s \n", conf);
	free(conf);
	}


	//init onion server thread
	OnionServer* onion = new OnionServer(settingMMTT, settingKinect); 
	onion->start_server();

	MyTuioServer25D tuio;

	//saves settings
	//settingMMTT->saveConfigFile("settingMMTT.json");
	//settingKinect->saveConfigFile("settingKinectDefault.json");

	ImageAnalysis* ia;
	//Freenect::Freenect freenect;
	//MyFreenectDevice& device = freenect.createDevice<MyFreenectDevice>(0); 
	Freenect::Freenect* freenect;
	MyFreenectDevice* device;
	Tracker tracker(settingKinect);

	if(withKinect){
		freenect = new Freenect::Freenect;
		/* wie kann ich mir den umweg über mydevice sparen?!*/
		MyFreenectDevice& mydevice = freenect->createDevice<MyFreenectDevice>(0); 
		device = &mydevice;

		ia = new ImageAnalysis(device, settingKinect);

		//Set Signals
		settingKinect->updateSig.connect(boost::bind(&MyFreenectDevice::update,device, _1, _2));
		settingKinect->updateSig.connect(boost::bind(&ImageAnalysis::resetMask,ia, _1, _2));

		//device.startVideo();
		device->startDepth();

		/* This should fix the problem, that opencv window did not closed on quit.
		 * See http://stackoverflow.com/questions/8842901/opencv-closing-the-image-display-window
		 * But I see no advancement.
		 */
		//cvStartWindowThread();

		namedWindow("img",CV_WINDOW_AUTOSIZE);
	}


	while (!die) {
		//device.getVideo(rgbMat);
		//cv::imshow("rgb", rgbMat);
		//device.getDepth(depthMat);

		//get 8 bit depth image
		if(withKinect){
			FunctionMode mode = settingMMTT->getModeAndLock();

			switch (mode){
				case DEPTH_MASK_DETECTION:
					{
						 mode = ia->depth_mask_detection(); 
					}
					break;
				case HAND_DETECTION:
					{
						mode = ia->hand_detection(); 
						//find blobs
						//Mat foo = ia->m_areaMask(settingKinect->m_roi);
						tracker.trackBlobs(ia->m_filteredMat(settingKinect->m_roi), ia->m_areaMask, true);

						//send tuio
						tuio.send_blobs(tracker.getBlobs(), settingKinect->m_areas, settingKinect->m_roi);
					}
					break;
				case AREA_DETECTION_START:
						ia->m_area_detection_step = 0;
						imshowNbr = SHOW_AREAS;
				case AREA_DETECTION:
				default:
					{
						mode = ia->area_detection(&tracker);
					}
					break;
			}
			settingMMTT->unlockMode(mode);
			/*
				 _tmpThresh->origin = 1;
				 _tmpThresh->imageData = (char*) depthf.data;
				 _newblobresult = new CBlobResult(_tmpThresh, NULL, 0, false);

				 _newblobresult->Filter( *_newblobresult, B_EXCLUDE, CBlobGetArea(), B_GREATER, val_blob_maxsize.internal_value );
				 _newblobresult->Filter( *_newblobresult, B_EXCLUDE, CBlobGetArea(), B_LESS, val_blob_minsize.internal_value );
				 */

			switch (imshowNbr){
				case SHOW_DEPTH:
					cv::imshow("img",ia->m_depthf(settingKinect->m_roi));
					break;
				case SHOW_AREAS:
					cv::imshow("img",ia->getColoredAreas()(settingKinect->m_roi) );
					break;
				case SHOW_MASK:
					cv::imshow("img",ia->m_depthMask(settingKinect->m_roi));
					break;
				case SHOW_FILTERED:
					cv::imshow("img",ia->m_filteredMat(settingKinect->m_roi));
					break;
				case SHOW_FRONTMASK:
					cv::imshow("img",ia->getFrontMask()(settingKinect->m_roi) );
					break;
				default:
					break;
			}

		}else{
			sleep(1);
		}

		char k = cvWaitKey(10);
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
		if( k > 48 && k<58 ){ // '1'<=k<='9'
			imshowNbr = k-48;			
		}
		if(iter >= 20000) break;
		iter++;
	}

	/* Clean up objects */
	delete onion;

	if(withKinect){
		//device->stopVideo();
		//device->stopDepth();
		delete ia;
		delete freenect;
		//cvDestroyWindow("img");
		cvDestroyAllWindows();

		//wait some time to give img-window enouth time to close.
		cvWaitKey(1);//no, did not work on linux. Use cvStartWindowThread()
	}

	delete settingKinect;
	delete settingMMTT;

	return 0;
}

