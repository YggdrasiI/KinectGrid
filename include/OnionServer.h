#ifndef ONIONSERVER_H
#define ONIONSERVER_H

#include <string>
#include <vector>
#include <iostream>
//#include <pthread.h>
//#include <png.h>

#include <stdarg.h>

//#include <onion/onion.h>
//#include <onion/dict.h>
#include <onion/log.h>
#include <onion/onion.hpp>
#include <onion/response.hpp>
#include <onion/request.hpp>
#include <onion/handler.hpp>
#include <onion/dict.hpp>
#include <onion/url.hpp>

//#include <onion/mime.h>
//#include <onion/extras/png.h>

#include <boost/signals2/signal.hpp>
//#include <boost/bind.hpp>

#include "JsonConfig.h"

class SettingKinect;


//thread function
static void* start_myonion_server(void* arg){
	printf("Onion server: Start listening.\n");
	((Onion::Onion*)arg)->listen();//loop
	printf("Onion server: Stop listening.\n");
	return NULL; // This is equivalent to calling pthread_exit(3)
	             // with the value supplied in the return statement.
}

// Signal return value combiner. 
template<typename T>
struct maximum
{
	typedef T result_type;

	template<typename InputIterator>
		T operator()(InputIterator first, InputIterator last) const
		{
			// If there are no slots to call, just return the
			// default-constructed value
			if (first == last)
				return T();

			T max_value = *first++;
			while (first != last) {
				if (max_value < *first)
					max_value = *first;
				++first;
			}

			return max_value;
		}
};

// Signal return value combiner. 
/*
 * -3: No data written into reply, but input processed successful.
 * -2: No data written into reply. Input generate state which require reloading of web page.
 * -1: No data written into reply. Input has generate error. (Currently not used.)
 *  0: data written into reply
 *  1: two signals wrote data. The output is likely unuseable
 *  2: data written, but undefined error occours.
 *
 * Transition map:
 * (i,j) => max(i,j), i∈[-3,…,-1], j∈[-3,…,0]
 * (0,j) => 0, j < 0
 * (0,0) => 1
 * (0,1) => 1
 * (1,0) => 1
 * (1,2) => 2
 * (2,j) => 2
 */
template<typename T>
struct http_signal_mixer
{
	typedef T result_type;

	template<typename InputIterator>
		T operator()(InputIterator first, InputIterator last) const
		{
			// If there are no slots to call, just return the
			// default-constructed value
			if (first == last)
				return T();

			VPRINT("http sig %i, ", *first);
			T ret_value = *first;
			++first;
			while (first != last) {
				VPRINT(" %i, ", *first);
				if( ret_value < (T)0 ){
					if (ret_value < *first)
						ret_value = *first;
				}else if( ret_value == (T)0){
					if ( (T)0 <= *first ){
						ret_value = (T)1;
					}
				}else{ // ret_value > 0
					ret_value = std::max<T>(ret_value, *first);
				}
				++first;
			}

			VPRINT(" => %i\n", ret_value);
			return ret_value;
		}
};

class OnionServer{
	private:	
		pthread_t m_pthread;
		Onion::Onion m_onion;
		Onion::Url m_url;
		/* Store header with mime type and charset information for several file extensions.
		 * This is just a workaround. There should be an automatic mechanicm
		 * in libonion. */
		Onion::Dict m_mimedict;

		/* This arrays saves some strings. Most
		 * functions of onion cpp binding use 
		 * references to string. Thus we need
		 * to omit local variables.
		 * */
		//std::vector<std::string> m_urls;
		std::vector<std::string> m_mimes;

		SettingKinect &m_settingKinect;
		View m_view;
	public:
		OnionServer(SettingKinect &settingKinect );
		
		~OnionServer()
		{
			//stop_server();
		}

		int start_server();
		int stop_server();

		/* Update signal. Called by sending of data by js script.
		 *	Every signal handler gain access to
		 *	- the raw request req,
		 *	- the get param 'actionid' and,
		 *	- the response data res
		 * Signal returns false, if no signall handler wrote into res.
		 * For each actionid should only one signal handler wrote into the response struture res.
		 *	*/
		boost::signals2::signal<int (Onion::Request *preq, int actionid, Onion::Response *pres ),
			//maximum<int> > updateSignal;
			http_signal_mixer<int> > updateSignal;

		/* Update signal handler of this class.*/
		int updateWebserver(Onion::Request *preq, int actionid, Onion::Response *pres);

		/* The user can select a new view over the webinterface (thread A), but this
		 * thread can not set the view variable (mainly used in thread B) of the setting
		 * struct without blocking for a unknown amount of time.
		 * Thus, the webinterface caches new values locally. This will be read by thread B 
		 * later.
		 * If no new view was selected, the input value will be reflected. 
		 */
		View getView(View in);

	private:
		void setupUrls();

		/* Handler for webinterface requests */
		onion_connection_status index_html( Onion::Request &req, Onion::Response &res);
		onion_connection_status updateData( Onion::Request &req, Onion::Response &res);
		onion_connection_status getSettingKinect( Onion::Request &req, Onion::Response &res);
		onion_connection_status getSettingKinectWrapped( Onion::Request &req, Onion::Response &res);
		onion_connection_status search_file( Onion::Request &req, Onion::Response &res);

		onion_connection_status getPrinterMessages( Onion::Request &req, Onion::Response &res);
		//onion_connection_status getJobFolder( Onion::Request &req, Onion::Response &res);
		//onion_connection_status getJobFolderWrapped( Onion::Request &req, Onion::Response &res);
		onion_connection_status preview( Onion::Request &req, Onion::Response &res);
};

#endif
