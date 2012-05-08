#ifndef MYTUIOSERVER25D_H
#define MYTUIOSERVER25D_H

#include "TuioServer25D.h"
#include "TuioCursor25D.h"

#include <stdlib.h>
#include <vector>
#include <cv.h>
#include "constants.h"
#include "blob.h"

using namespace TUIO;

class MyTuioServer25D: public TuioServer25D {
	public:
		MyTuioServer25D(const char *host, int port): TuioServer25D(host, port), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
			disablePeriodicMessages();
		};
		MyTuioServer25D(): TuioServer25D(), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
			disablePeriodicMessages();
		};
		~MyTuioServer25D() { };
		void send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi);

private:
		TuioCursor25D *cursor;
		TuioTime currentTime;
		bool verbose;

		//void processEvents();

};

#endif
