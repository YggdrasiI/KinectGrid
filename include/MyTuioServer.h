#ifndef MYTUIOSERVER_H
#define MYTUIOSERVER_H

#include "TuioServer.h"
#include "TuioCursor.h"

#include <stdlib.h>
#include <vector>
#include "blob.h"

using namespace TUIO;

class MyTuioServer: public TuioServer {
	public:
		MyTuioServer(const char *host, int port): TuioServer(host, port), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
		};
		MyTuioServer(): TuioServer(), verbose(false){
			verbose = true;
			currentTime = TuioTime::getSessionTime();
			//tuioServer->enablePeriodicMessages();
		};
		~MyTuioServer() { };
		void send_blobs(std::vector<cBlob>& blobs);
	private:
		TuioCursor *cursor;
		TuioTime currentTime;
		bool verbose;

		//void processEvents();

};

#endif
