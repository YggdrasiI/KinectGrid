#ifndef MYTUIOSERVER_H
#define MYTUIOSERVER_H

#include "TuioServer.h"
#include "TuioCursor.h"

#include <stdlib.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include "constants.h"
#include "blob.h"

using namespace TUIO;

class MyTuioServer: public TuioServer {
	public:
		MyTuioServer(const char *host, int port): TuioServer(host, port){
			currentTime = TuioTime::getSessionTime();
			//enablePeriodicMessages();
			disablePeriodicMessages();
		};
		MyTuioServer(): TuioServer(){
			currentTime = TuioTime::getSessionTime();
			//enablePeriodicMessages();
			disablePeriodicMessages();
		};
		~MyTuioServer() { };
		void send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi);

private:
		TuioCursor *cursor;
		TuioTime currentTime;
		//void processEvents();
};

#endif
