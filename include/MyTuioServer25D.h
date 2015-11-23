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
		MyTuioServer25D(const char *host, int port): TuioServer25D(host, port){
			currentTime = TuioTime::getSessionTime();
			//enablePeriodicMessages();
			disablePeriodicMessages();
		};
		MyTuioServer25D(): TuioServer25D(){
			currentTime = TuioTime::getSessionTime();
			//enablePeriodicMessages();
			disablePeriodicMessages();
		};
		~MyTuioServer25D() { };
		/* minDepth and maxDepth:
		 *    Controls scaling of depth values. 
		 *    Normalization (mapping on [0,1) will be applied on
		 *    [max(minDepth,area.depth), maxDepth).
		*/
		void send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi, int minDepth=0, int maxDepth=255);

private:
		TuioCursor25D *cursor;
		TuioTime currentTime;
		//void processEvents();
};

#endif
