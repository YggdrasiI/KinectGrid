#include <iostream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <boost/signals2/signal.hpp>
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

void print_help(){
	printf(
			"--config/-c [filename]: Load settings from filename.\n"
			"--display/-d [x11|web|none]: Select output for images.\n"
			"--sleep/-s:    Reduce refresh rate of blob detection if no activity was noticed.\n"
			"--rgb:      Start Kinect with video mode (Debugging)\n"
			"--no-kinect: Omit kinect usage and just start webserver (Debugging)\n"
			"--help/-h:  Show this help text\n\n"
			);
}

/* Callback for mouseclick in OpenCV window.
 * Used for area detection.
 */
struct OnMouseData{
	ImageAnalysis *ia;
	SettingKinect *pSettingKinect;
};

static void cvOnMouse( int event, int x, int y, int flags, void* userdata) {
	if( event != cv::EVENT_LBUTTONDOWN )
		return;
	OnMouseData *data = (OnMouseData*)userdata;	
	if( data->ia == NULL || data->pSettingKinect == NULL ){
		VPRINT("Userdata pointer of mouse handler NULL.\n");
		return;
	}

	FunctionMode mode = data->pSettingKinect->getModeAndLock();
	if( mode == AREA_DETECTION ){
		VPRINT("Mouse callback! event=%i point(%i,%i)\n", event, x, y);
		data->ia->area_detection_opencv_click(x,y);
	}
	data->pSettingKinect->unlockMode(mode);
}


int main(int argc, char **argv) {

	// Main state variables
	bool die(false);
  bool withKinect(true);
	bool rgbMode(false);
	bool sleepMode(false);

	uint32_t sleepSeconds = 0;
	DisplayMode displayMode = DISPLAY_MODE_NONE;
	std::string configfile("default_settings.json");
	string filename("snapshot");
	string suffix(".png");
	Fps fps;

	// Handle input arguments
	for( int i=1; i<argc; ++i ){
		if( strcmp("-h",argv[i]) == 0 || strcmp("--help",argv[i]) == 0 ){
			print_help();
			return 0;
		}
		if( strcmp("--no-kinect",argv[i]) == 0 || strcmp("--noKinect",argv[i]) == 0 ){
			withKinect = false;
			continue;
		}
		if( strcmp("-s",argv[i]) == 0 || strcmp("--sleep",argv[i]) == 0 ){
			sleepMode = true;
			continue;
		}
		if( strcmp("--rgb",argv[i]) == 0 ){
			rgbMode = true;
			continue;
		}
		if( strcmp("-d",argv[i]) == 0 || strcmp("--display",argv[i]) == 0 ){
			displayMode = DISPLAY_MODE_NONE;
			if( i+1<argc ){
				if( strcmp("web", argv[i+1]) == 0){
					displayMode = DISPLAY_MODE_WEB;
					++i;
				}else
				if( strcmp("x11", argv[i+1]) == 0){
					displayMode = DISPLAY_MODE_CV;
					++i;
				}else
				if( strcmp("directfb", argv[i+1]) == 0){
					displayMode = DISPLAY_MODE_NONE; //todo
					++i;
				}else
				if( strcmp("none", argv[i+1]) == 0){
					displayMode = DISPLAY_MODE_NONE; 
					++i;
				}else
				if( strncmp("-", argv[i+1], 1) != 0){
					printf("Unknown argument for %s: %s.\n", argv[i], argv[i+1]);
					++i;
				}else{
					printf("Missing argument for %s.\n", argv[i]);
				}
			}
			continue;
		}
		if( strcmp("-c", argv[i]) == 0 || strcmp("--config", argv[i]) == 0 ){
			if( i+1<argc ){
				if( strncmp("-", argv[i+1], 1) != 0){
					configfile = argv[i+1];
					++i;
				}else{
					printf("Missing argument for %s.\n", argv[i]);
				}
			}
			continue;
		}
		std::cout << "Unknown command line option: " << argv[i] << std::endl;
	}

	//Load & Create settings
	SettingKinect settingKinect(withKinect);
	settingKinect.init(configfile.c_str());

	if( !withKinect ) settingKinect.m_displayMode = DISPLAY_MODE_NONE;
	if( rgbMode ) settingKinect.m_view = VIEW_RGB;


	//init onion server thread
	OnionServer onion(settingKinect); 
	onion.start_server();

	MyTuioServer tuio(
			settingKinect.getString("tuio2Dcur_host"),
			(int) settingKinect.getNumber("tuio2Dcur_port"));
	MyTuioServer25D tuio2(
			settingKinect.getString("tuio25Dblb_host"),
			(int) settingKinect.getNumber("tuio25Dblb_port"));


	ImageAnalysis* ia;
	Freenect::Freenect* freenect;
	MyFreenectDevice* device;
#ifdef MYBLOB
	Tracker2 tracker(&settingKinect);
#else
	TrackerCvBlobsLib tracker(&settingKinect);
#endif
	View &eView = settingKinect.m_view;
	OnMouseData mouseData = {NULL, &settingKinect};
	time_t last_blob_detection = time(NULL);

	settingKinect.m_displayMode = displayMode;

	if(withKinect){
		freenect = new Freenect::Freenect;
		MyFreenectDevice& mydevice = freenect->createDevice<MyFreenectDevice>(0); 
		device = &mydevice;

		ia = new ImageAnalysis(device, &settingKinect);
		mouseData.ia = ia;

		//Set Signals
		settingKinect.updateSig.connect( boost::bind(&MyFreenectDevice::update,device, _1, _2) );
		settingKinect.updateSig.connect( boost::bind(&ImageAnalysis::resetMask,ia, _1, _2) );

		onion.updateSignal.connect( boost::bind(&ImageAnalysis::http_actions, ia, _1, _2, _3) );
		if( settingKinect.m_displayMode == DISPLAY_MODE_WEB ) {
			onion.updateSignal.connect( boost::bind(&ImageAnalysis::getWebDisplayImage, ia, _1, _2, _3) );
		}

		if( rgbMode )
			device->startVideo();
		else
			device->startDepth();

		/* This should fix the problem, that opencv window did not closed on quit.
		 * See http://stackoverflow.com/questions/8842901/opencv-closing-the-image-display-window
		 * But I see no advancement.
		 */
		//cvStartWindowThread();
		if( settingKinect.m_displayMode == DISPLAY_MODE_CV ) {
			cv::namedWindow("img",CV_WINDOW_AUTOSIZE);
			cv::setMouseCallback("img", cvOnMouse, &mouseData);
		}

		if( rgbMode ){
			settingKinect.setMode(RGB);
		}else{
			//Set mode to LOAD_MASKS. This try to load masks and repoke areas.
			settingKinect.setMode(LOAD_MASKS);
		}
	}

	/* Local needs to be set to avoid errors with printf + float values.
	 * Gtk:Window changes locale...*/
	setlocale(LC_NUMERIC, "C");

	// Main loop
	while (!die) {

		if( withKinect ){

			FunctionMode mode = settingKinect.getModeAndLock();
			switch (mode){
				case RGB:	
					{
						if( settingKinect.m_kinectProp.clipping)
							device->setRoi(true,settingKinect.m_kinectProp.roi);
						else
							device->setRoi(false,Rect(0,0,0,0));

						while( !device->getVideo(ia->m_rgb) ){
							usleep(50);
						}
						mode = RGB;
					}
					break;
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
						tracker.trackBlobs(ia->m_filteredMat(settingKinect.m_kinectProp.roi), ia->m_areaMask, true, &settingKinect.m_areas);

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
						const char* sname = settingKinect.getString("masks");
						bool loadingFailed(false);

						std::ostringstream frame;
						frame << sname << "_frame" << ".png";
						Mat tmpLoadImg0 = cv::imread(frame.str(),0);
						if(tmpLoadImg0.empty()) {
							VPRINT("[Note] Can't load frame mask '%s'.\n", frame.str().c_str() );
							loadingFailed = true;
						}else{
							ia->m_areaGrid = tmpLoadImg0;
						}

						std::ostringstream depth;
						depth << sname << "_depth" << ".png";
						Mat tmpLoadImg1 = cv::imread(depth.str(),0);
						if(tmpLoadImg1.empty()) {
							VPRINT("[Note] Can't load depth mask '%s'.\n", depth.str().c_str() );
							loadingFailed = true;
							//ia->m_depthMaskWithoutThresh = Scalar(0); //optional
						}else{
							ia->m_depthMaskWithoutThresh = tmpLoadImg1;
						}

						// repoke to generate m_areaMask and eval position+dimensions of areas.
						if( loadingFailed ){
							ia->resetMask(&settingKinect, FRONT_MASK);
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
						const char* sname = settingKinect.getString("masks");

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
					ia->m_area_detection_step = AREA_DETECTION_STEP_FINISH;
					mode = ia->area_detection(&tracker);
					break;
				case AREA_DETECTION_START:
					ia->m_area_detection_step = AREA_DETECTION_STEP_INIT;
					eView = VIEW_AREAS;
					mode = ia->area_detection(&tracker);
					break;
				case AREA_DETECTION:
					{
						mode = ia->area_detection(&tracker);
						if( ia->m_area_detection_step == AREA_DETECTION_STEP_BY_CLICK){
							//Debug, Slow down because above function returns immediately.
							settingKinect.unlockMode(mode);
							usleep(50000);		
							mode = settingKinect.getModeAndLock();
						}
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

			//check if webserver (other thread) has got new viewnumber.
			eView = onion.getView(eView);

			// Replace depth view with rgb view if rgb mode is on.
			if( rgbMode && eView == VIEW_DEPTH ) eView = VIEW_RGB;

			// Display images
			if( settingKinect.m_displayMode == DISPLAY_MODE_CV ) {
				switch (eView){
					case VIEW_DEPTH:
						cv::imshow("img",ia->m_depthf(settingKinect.m_kinectProp.roi));
						break;
					case VIEW_AREAS:
						cv::imshow("img",ia->getColoredAreas()(settingKinect.m_kinectProp.roi) );
						break;
					case VIEW_MASK:
						cv::imshow("img",ia->m_depthMask(settingKinect.m_kinectProp.roi));
						break;
					case VIEW_FILTERED:
						cv::imshow("img",ia->m_filteredMat(settingKinect.m_kinectProp.roi));
						break;
					case VIEW_FRONTMASK:
						cv::imshow("img",ia->getFrontMask()(settingKinect.m_kinectProp.roi) );
						break;
					case VIEW_RGB:
						cv::imshow("img",ia->m_rgb(settingKinect.m_kinectProp.roi));
						break;
					default:
						break;
				}
			}

			/* Reset flag for volatile images. */
			if( settingKinect.m_displayMode == DISPLAY_MODE_WEB ) {
				switch (eView){
					case VIEW_DEPTH:
					case VIEW_RGB:
					case VIEW_AREAS:
					case VIEW_FILTERED:
					default:
						ia->m_png_redraw = true; 
						break;
				}
			}

			fps.next(stdout);

			//if mode is HAND_DETECTION and long time no blob was detected, sleep.
			if( sleepMode && mode == HAND_DETECTION ){
				if( tracker.getBlobs().size() < 1 ){
					if( time(NULL) - last_blob_detection  > 10 ){
						VPRINT("Sleep mode, wait 2 seconds for next frame...\n");
						sleepSeconds = 2;
					}
				}else{
					last_blob_detection = time(NULL);
					sleepSeconds = 0;
				}
			}

		}else{ //without Kinect
			FunctionMode mode = settingKinect.getModeAndLock();
			if( mode == QUIT ){
				printf("End main loop\n");
				die = true;
			}
			settingKinect.unlockMode(mode);
		}

		// Idle and wait on user input
		if( settingKinect.m_displayMode == DISPLAY_MODE_CV ) {
			char k = cvWaitKey(10+1000*sleepSeconds);
			if( k == 27 ){
				printf("End main loop\n");
				die = true;
				break;
			}
			if( k == 8 ) {
				/*
					 std::ostringstream file;
					 file << filename << i_snap << suffix;
					 cv::imwrite(file.str(),ia->m_rgb);
					 i_snap++;
					 */
			}
			if( k > 48 && k<58 ){ // '1'<=k<='9'
				eView = (View) (k-48);
				ia->m_png_redraw = true; // new image available
			}

		}else{
			if( sleepSeconds>0 )
				sleep(sleepSeconds);
		}

	}

	printf("Shutdown KinectGrid...\n");

	if(withKinect){
		if(rgbMode)
			device->stopVideo();
		else
			device->stopDepth();

		delete ia;
		delete freenect;
		cvDestroyAllWindows();

		//wait some time to give img-window enouth time to close.
		cvWaitKey(10);
	}

	/* Clean up objects */
	sleep(1);
	onion.stop_server();
	sleep(1);


	return EXIT_SUCCESS;
}

