#ifndef MYTUIOSERVER_H
#define MYTUIOSERVER_H

#include "TuioServer25D.h"
#include "TuioCursor25D.h"

#include <stdlib.h>
#include <vector>
#include <cv.h>
#include "constants.h"
#include "blob.h"

using namespace TUIO;

class MyTuioServer: public TuioServer25D {
	public:
		MyTuioServer(const char *host, int port): TuioServer25D(host, port), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
		};
		MyTuioServer(): TuioServer25D(), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
		};
		~MyTuioServer() { };
		void send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi);

private:
		TuioCursor25D *cursor;
		TuioTime currentTime;
		bool verbose;

		//void processEvents();

};

#endif
