#ifndef ONIONSERVER_H
#define ONIONSERVER_H

#include <pthread.h>
#include <png.h>

#include <onion/log.h>
#include <onion/onion.h>
#include <onion/dict.h>
#include <onion/extras/png.h>

#include "JsonConfig.h"
#include "SettingKinect.h"
#include "SettingMMTT.h"


/* Declare jSON data object here
 *
 *
 */


//thread function
static void* start_myonion_server(void* arg){
	printf("Onion server: Start listening.\n");
	onion_listen((onion*)arg);//loop
	printf("Onion server: Stop listening.\n");
}

class OnionServer{
	public:	
		onion* m_ponion;
		pthread_t m_pthread;
	private:
		SettingMMTT* m_psettingMMTT;
		SettingKinect* m_psettingKinect;
		int m_view;
	public:
		OnionServer(SettingMMTT* psettingMMTT, SettingKinect* psettingKinect):
			m_ponion( onion_new(O_THREADED) ),
			m_pthread(),
			m_view(-1),
			m_psettingMMTT(psettingMMTT),
			m_psettingKinect(psettingKinect)
		{
			//start_server();
		}
		~OnionServer()
		{
			if(m_ponion != NULL) stop_server();
		}

		int start_server();
		int stop_server();
		int updateSetting(onion_request *req, onion_response *res);
		/* returns selected view if webserver get new view number. Otherwiese in will reflected*/
		int getView(int in){
			if(m_view < 0) return in;
			int ret = m_view;
			m_view = -1;
			return ret;
		};

};

#endif
