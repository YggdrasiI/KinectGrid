#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <boost/signal.hpp>
#include <boost/bind.hpp>

//for usleep
#include <unistd.h>

#include "constants.h"
#include "MyFreenectDevice.h"
#include "ImageAnalysis.h"
#include "BlobResult.h"
#include "JsonConfig.h"
#include "OnionServer.h"
#include "MyTuioServer.h"
#include "MyTuioServer25D.h"

#ifdef MYBLOB
#include "Tracker2.h"
#else
#include "TrackerCvBlobsLib.h"
#endif


#include <locale.h>
//#include <time.h>
#include <sys/time.h>

// Selection of output image
enum Show {SHOW_NONE=0,SHOW_DEPTH=1,SHOW_MASK=2,SHOW_FILTERED=3,SHOW_AREAS=4,SHOW_FRONTMASK};

// for FPS estimation.
class Fps
{
private:
	int frame;
	int mod;
	struct timeval earlier;
	struct timeval later;
	struct timeval interval;
	long long diff;
	void tic(){
		if(gettimeofday(&earlier,NULL))
			perror("first gettimeofday()");
	}

	void toc(){
		if(gettimeofday(&later,NULL))
			perror("first gettimeofday()");
		else
			diff = timeval_diff(&interval, &later, &earlier);
	}
	long long
		timeval_diff(struct timeval *difference,
				struct timeval *end_time,
				struct timeval *start_time
				)   
		{
			struct timeval temp_diff;

			if(difference==NULL)
			{
				difference=&temp_diff;
			}

			difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
			difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

			/* Using while instead of if below makes the code slightly more robust. */

			while(difference->tv_usec<0)
			{
				difference->tv_usec+=1000000;
				difference->tv_sec -=1;
			}

			return 1000000LL*difference->tv_sec+
				difference->tv_usec;

		} /* timeval_diff() */

public:
	void next(FILE *stream){
		frame++;
		if( frame%mod == 0){
			toc();
			if( stream != NULL ){
				double fps = (1000000*(double)mod)/diff;
				fprintf(stream, "frames: %i, dt: %4.1f ms \tfps: %4.2f\n", mod , diff/1000.0, fps );
			}
			tic();
		}
	}

	Fps():frame(0),mod(300){ 
			tic();
		}
};

int main(int argc, char **argv) {
	bool die(false);
  bool withKinect(true);
	int imshowNbr = SHOW_NONE; 
	string filename("snapshot");
	string suffix(".png");
	int iter(0);
	Fps fps;

	bool sleepmode(false);
	bool rgbmode(false);
	if( argc > 1){
		int wk = atoi(argv[1]);
		if(wk==0) withKinect = false;
		if(wk==1) sleepmode = true;
		if(wk==2) rgbmode = true; /* just for debugging libfreenect */
	}

	time_t last_blob_detection = time(NULL);

	//Load & Create settings
	SettingKinect settingKinect;
	settingKinect.init("default_settings.json");
	/*
	if (settingKinect.init( settingKinectGrid->getString("lastSetting") )){
		//Kinect settings did not found.
		printf("File %s was not found. Use default values.\n", 
				settingKinectGrid.getString("lastSetting") );
	}*/

	//init onion server thread
	OnionServer* onion = new OnionServer(settingKinect); 
	onion->start_server();

	MyTuioServer tuio(
			settingKinect.getString("tuio2Dcur_host"),
			(int) settingKinect.getNumber("tuio2Dcur_port"));
	MyTuioServer25D tuio2(
			settingKinect.getString("tuio25Dblb_host"),
			(int) settingKinect.getNumber("tuio25Dblb_port"));


	ImageAnalysis* ia;
	//Freenect::Freenect freenect;
	//MyFreenectDevice& device = freenect.createDevice<MyFreenectDevice>(0); 
	Freenect::Freenect* freenect;
	MyFreenectDevice* device;
#ifdef MYBLOB
	Tracker2 tracker(&settingKinect);
#else
	TrackerCvBlobsLib tracker(&settingKinect);
#endif

	if(withKinect){
		freenect = new Freenect::Freenect;
		/* wie kann ich mir den umweg über mydevice sparen?!*/
		MyFreenectDevice& mydevice = freenect->createDevice<MyFreenectDevice>(0); 
		device = &mydevice;

		ia = new ImageAnalysis(device, &settingKinect);

		//Set Signals
		settingKinect.updateSig.connect(boost::bind(&MyFreenectDevice::update,device, _1, _2));
		settingKinect.updateSig.connect(boost::bind(&ImageAnalysis::resetMask,ia, _1, _2));

		if( rgbmode )
			device->startVideo();
		else
			device->startDepth();

		/* This should fix the problem, that opencv window did not closed on quit.
		 * See http://stackoverflow.com/questions/8842901/opencv-closing-the-image-display-window
		 * But I see no advancement.
		 */
		//cvStartWindowThread();

		namedWindow("img",CV_WINDOW_AUTOSIZE);

		//Set mode to LOAD_MASKS. This try to load masks and repoke areas.
		settingKinect.setMode(LOAD_MASKS);
	}

	/* Local needs to be set to avoid errors with printf + float values.
	 * Gtk:Window changes locale...*/
	setlocale(LC_NUMERIC, "C");

	while (!die) {

		if( rgbmode ){
			Mat rgbMat(Size(640,480),CV_8UC3,Scalar(0));

			if( settingKinect.m_kinectProp.clipping)
				device->setRoi(true,settingKinect.m_kinectProp.roi);
			else
				device->setRoi(false,Rect(0,0,0,0));

			while( !device->getVideo(rgbMat) ){
				usleep(50);
			}

			imshowNbr = onion->getView(imshowNbr);			
			switch (imshowNbr){
				case SHOW_DEPTH:
					cv::imshow("img",rgbMat);
					break;
				case SHOW_MASK:
					cv::imshow("img",rgbMat(settingKinect.m_kinectProp.roi));
			}


			fps.next(stdout);

		//get 8 bit depth image
		}else if(withKinect){
			FunctionMode mode = settingKinect.getModeAndLock();

			switch (mode){
				case REPOKE_DETECTION:
					{
						ia->resetMask(&settingKinect, REPOKE);
						mode = HAND_DETECTION;
					}
					break;
				case DEPTH_MASK_DETECTION:
					{
						mode = ia->depth_mask_detection(); 
					}
					break;
				case HAND_DETECTION:
					{
						mode = ia->hand_detection(); 
						//find blobs
						//Mat foo = ia->m_areaMask(settingKinect.m_kinectProp.roi);
						tracker.trackBlobs(ia->m_filteredMat(settingKinect.m_kinectProp.roi), ia->m_areaMask, true, &settingKinect.m_kinectProp.areas);

						//send tuio
						if( settingKinect.m_tuioProtocols[0] )
							tuio.send_blobs(tracker.getBlobs(), settingKinect.m_areas, settingKinect.m_kinectProp.roi);
						if( settingKinect.m_tuioProtocols[1] )
							tuio2.send_blobs(tracker.getBlobs(), settingKinect.m_areas, settingKinect.m_kinectProp.roi);
					}
					break;
				case LOAD_MASKS:
					{
						//filename (with extension....)	
						//const char* sname = settingKinectGrid.getString("lastSetting");
						const char* sname = "maskTODO";
						bool loadingFailed = false;

						std::ostringstream frame;
						frame << sname << "_frame" << ".png";
						Mat tmpLoadImg0 = cv::imread(frame.str(),0);
						if(tmpLoadImg0.empty()) {
							printf("[Note] Can't load depth mask %s_depth.png. \n", sname );
							loadingFailed = true;
						}else{
							ia->m_areaGrid = tmpLoadImg0;
						}

						std::ostringstream depth;
						depth << sname << "_depth" << ".png";
						Mat tmpLoadImg1 = cv::imread(depth.str(),0);
						if(tmpLoadImg1.empty()) {
							printf("[Note] Can't load depth mask %s_depth.png. \n", sname );
							loadingFailed = true;
						}else{
							ia->m_depthMaskWithoutThresh = tmpLoadImg1;
						}

						// repoke to generate m_areaMask and eval position+dimensions of areas.
						if( loadingFailed){
							mode = HAND_DETECTION;
						}else{
							//set some flags to avoid possible new evaluation of front/depth mask.
							ia->m_maskFront_ok = true;
							ia->finishDepthMaskCreation(); //set m_depthMaskCounter to zero;

							mode = REPOKE_DETECTION;
						}
					}
					break;
				case SAVE_MASKS:
					{
						//filename (with extension....)	
						//const char* sname = settingKinectGrid.getString("lastSetting");
						const char* sname = "maskTODO";

						std::ostringstream frame;
						frame << sname << "_frame" << ".png";
						cv::imwrite(frame.str(),ia->m_areaGrid);

						std::ostringstream depth;
						depth << sname << "_depth" << ".png";
						cv::imwrite(depth.str(),ia->m_depthMaskWithoutThresh);

						//This image gives only an overview and is irrelevant.
						std::ostringstream area;
						area << sname << "_area" << ".png";
						//cv::imwrite(area.str(),ia->m_areaMask);
						cv::imwrite(area.str(),ia->getColoredAreas());

						mode = HAND_DETECTION;
					}
					break;
				case AREA_DETECTION_END:
					ia->m_area_detection_step = 3;
					mode = ia->area_detection(&tracker);
					break;
				case AREA_DETECTION_START:
					ia->m_area_detection_step = 0;
					imshowNbr = SHOW_AREAS;
				case AREA_DETECTION:
					{
						mode = ia->area_detection(&tracker);
					}
					break;
				case QUIT:
				default:
					{
						printf("End main loop\n");
						die = true;
					}
					break;
			}
			settingKinect.unlockMode(mode);

			//check if webserver get new viewnumber
			imshowNbr = onion->getView(imshowNbr);

			switch (imshowNbr){
				case SHOW_DEPTH:
					cv::imshow("img",ia->m_depthf(settingKinect.m_kinectProp.roi));
					break;
				case SHOW_AREAS:
					cv::imshow("img",ia->getColoredAreas()(settingKinect.m_kinectProp.roi) );
					break;
				case SHOW_MASK:
					cv::imshow("img",ia->m_depthMask(settingKinect.m_kinectProp.roi));
					break;
				case SHOW_FILTERED:
					cv::imshow("img",ia->m_filteredMat(settingKinect.m_kinectProp.roi));
					break;
				case SHOW_FRONTMASK:
					cv::imshow("img",ia->getFrontMask()(settingKinect.m_kinectProp.roi) );
					break;
				default:
					break;
			}

			fps.next(stdout);

			//if mode is HAND_DETECTION and long time no blob was detected, sleep.
			if( sleepmode && mode == HAND_DETECTION ){
				if( tracker.getBlobs().size() < 1 ){
					if( time(NULL) - last_blob_detection  > 10 ){
						//printf("Sleep mode....\n");
						cvWaitKey(2000);
					}
				}else{
					last_blob_detection = time(NULL);
				}
			}

		}else{
			FunctionMode mode = settingKinect.getModeAndLock();
			if( mode == QUIT ){
				printf("End main loop\n");
				die = true;
			}
			settingKinect.unlockMode(mode);

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

		if(iter >= 2000000) break;
		iter++;
	}

	printf("Quitting KinectGrid...\n");

	/* Clean up objects */
	delete onion;

	if(withKinect){
		if(rgbmode)
			device->stopVideo();
		else
			device->stopDepth();

		delete ia;
		delete freenect;
		cvDestroyAllWindows();

		//wait some time to give img-window enouth time to close.
		cvWaitKey(10);
	}

	return EXIT_SUCCESS;
}

