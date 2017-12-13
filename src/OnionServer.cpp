/*
 * This class use the onion library from David Moreno.
 * See https://github.com/davidmoreno/onion .
	*/
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
//#include <sys/types.h>

#include <boost/bind.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/stream.hpp>
#include "boost/filesystem.hpp"
//#include <istream>
namespace fs = boost::filesystem;

#include "JsonMessage.h"
#include "SettingKinect.h"
#include "OnionServer.h"

/* Without this flag libonion creates an listening loop thread
 * on its own.
 * With this flag this class creates it's own thread by pthread.
 * I recommend the first variant because the second one produces
 * some issues at shutdown.
 */
//#define DETACH_MANUAL

// This has to be extern, as we are compiling C++
extern "C"{
onion_connection_status index_html_template(void *p, onion_request *req, onion_response *res);
onion_connection_status kinect_settings_js_template(void *p, onion_request *req, onion_response *res);
}

extern "C" {
	/* Replace default onion_log function to 
	 * to filter out O_INFO messages */
	void log_wrapper(onion_log_level level, const char *filename,
			int lineno, const char *fmt, ...){

		if( level == O_INFO) return;

		char tmp[256];
		va_list ap;
		va_start(ap, fmt);
		vsnprintf(tmp,sizeof(tmp),fmt, ap);
		va_end(ap);
		onion_log_stderr(level, filename, lineno, tmp);
	};

	void (*onion_log)(onion_log_level level, const char *filename,
			int lineno, const char *fmt, ...)=log_wrapper;
}

const std::string ErrNotFound = "<h1>File not found.</h1>";
const std::string ErrReadFailed = "<h1>Error while reading File.</h1>";

/* Helper functions */
static bool check_regex(const std::string &s, const std::string &pattern){
	boost::regex re;
	//std::string pattern("^[[:alnum:]]*\\.b9j$");
	//std::string s(filename);
	//std::cout << "String: " << s << std::endl << "Pattern: " << pattern << std::endl;
	try {
		re.assign(pattern, boost::regex_constants::icase);
	} catch (boost::regex_error& e) {
		std::cout << pattern << " is not a valid regular expression: \""
			<< e.what() << "\"" << std::endl;
	}

	if (boost::regex_match(s, re)) return true;
	return false;
}

static bool check_filename(const char *filename){
	const std::string s(filename);
	const std::string pattern("^[[:alnum:]]*\\.\\(jpg|png|html|js|css\\)$");
	return check_regex(s,pattern);
}

static bool check_configFilename(const char *filename){
	const std::string s(filename);
	const std::string pattern("^.*\\.json$");
	return check_regex(s,pattern);
}

/*
 * Parse data from client. Use actionid-arg to distinct different
 * cases.
 */
onion_connection_status OnionServer::updateData(
		Onion::Request &req, Onion::Response &res) {
	/* Default reply is 'reload' which force reload
	 * of complete website. In mosty cases this string will replaced
	 * by one of the signal handlers.
	 */
	int actionid = atoi( onion_request_get_queryd(req.c_handler(), "actionid","0") );

	const int updateResult = updateSignal( &req, actionid, &res);
	if( -3 == updateResult ){
		// Nothing was written. Write default reply (empty string).
		res.write("", 0);
	}
	else if( -2 == updateResult ){
		// Nothing was written and reload should be forced.
		std::string reply("reload");
		res.write(reply.c_str(), reply.size() );
	}

	return OCS_PROCESSED;
}

/*
 * Returns json struct of current settings.
 */
onion_connection_status OnionServer::getSettingKinect(
		Onion::Request &req, Onion::Response &res ){
	const char* kinect = m_settingKinect.getConfig(true);
	size_t len = strlen( kinect );
	res.write(kinect, (int) len );
	return OCS_PROCESSED;
}

/*
 Returns json struct of filenames in job files folder.
*/
/*
onion_connection_status OnionServer::getJobFolder(
		Onion::Request &req, Onion::Response &res ){

	std::string &folder = m_settingKinect.m_b9jDir;
	std::ostringstream json_reply;

	fs::path full_path( fs::initial_path<fs::path>() );
	full_path = fs::system_complete( fs::path( folder ) );

	unsigned long file_count = 0;

	json_reply << "{ \"name\" : \"" << folder << "\", \"content\" : [" ;

	if( !fs::exists( full_path ) ){
		std::cout << "Not found: " << full_path.filename() << std::endl;
		json_reply << "\"none\"";
	}else if ( !fs::is_directory( full_path ) ){
		std::cout << "Path is no directory: " << full_path.filename() << std::endl;
		json_reply << "\"none\"";
	}else{
		fs::directory_iterator end_iter;
		for ( fs::directory_iterator dir_itr( full_path );
				dir_itr != end_iter;
				++dir_itr )
		{
			try
			{
				if (! fs::is_directory( dir_itr->status() ) )
				{ //regluar file or symbolic link
					if( file_count ) json_reply << ", " << std::endl;
					json_reply << "{ \"" << file_count << "\":	" \
						<< dir_itr->path().filename() << " }";
					++file_count;
				}

			}
			catch ( const std::exception & ex )
			{
				std::cout << dir_itr->path().filename() << " " << ex.what() << std::endl;
			}
		}
	}

	json_reply << "] }" ;

	std::string json_replyStr = json_reply.str();
	size_t len = json_replyStr.size();
	res.write(json_replyStr.c_str(), (int) len );
	return OCS_PROCESSED;
}
*/


/* Like getJobFolder but with some prefix and suffix text
 * to get an *.js file.
 * */
/*
onion_connection_status OnionServer::getJobFolderWrapped(
		Onion::Request &req, Onion::Response &res ){
	res.write("json_job_files = ", 17);
	onion_connection_status ret = getJobFolder(req, res);
	res.write(";", 1);
	return ret;
}*/


/*
 * Convert all enties of message queue into json code and send this file
 * to the client.
 * Unused fragment of TinyPrint app.
 */
onion_connection_status OnionServer::getPrinterMessages(
		Onion::Request &req, Onion::Response &res ){

		Messages &q = m_settingKinect.m_queues;
		cJSON* tmp = jsonMessages("serialMessages", q.m_messageQueue);
		if( tmp != NULL ){
			char* json_serialMessages = cJSON_Print( tmp );
			size_t len = strlen( json_serialMessages );
			res.write(json_serialMessages, (int) len);

			cJSON_Delete(tmp);
			tmp = NULL;
			free(json_serialMessages);
			json_serialMessages = NULL;
		}else{
			const char* json_serialMessages = "(OnionServer) Serial Messages Error";
			size_t len = strlen( json_serialMessages );
			res.write(json_serialMessages, (int) len);
			//Do not free json_serialMessages in this case. It's point to static string here.
		}

	return OCS_PROCESSED;
}


/* SendSignal with actionid=HTTP_ACTION_GET_PREVIEW_IMAGE to get png image from
 * DisplayManager.
 */
onion_connection_status OnionServer::preview(
		Onion::Request &req, Onion::Response &res ){
	int actionid = HTTP_ACTION_GET_PREVIEW_IMAGE;
	if( -3 == updateSignal(&req, actionid, &res) ){
		//signals did not wrote into response. Write default reply.
		std::string reply("Could not generate Image.");
		res.write( reply.c_str(), reply.size() );
	}
	return OCS_PROCESSED;
}


/*
 Return raw file if found. Security risk?! Check of filename/path required?!
*/
onion_connection_status OnionServer::search_file(
		Onion::Request &req, Onion::Response &res ){
	//const char* path = onion_request_get_path(req);//Hm, is empty?!
	const char* path = onion_request_get_fullpath( req.c_handler() );
#ifdef VERBOSE
	printf("Request of %s.\n",path);
#endif
	std::string filename("./html/");
	filename.append(path);

	std::ifstream file(filename.c_str());
	std::string line;

	if( file.is_open()){

		/* Create header with mime type and charset information for several file extensions.
		 * This is just a workaround. There should be an automatic mechanicm
		 * in libonion. */
		int periodPos = filename.find_last_of('.');
		std::string extension = filename.substr(periodPos+1);
		std::string key("Content-Type");
		std::string defaultType("text/html; charset: utf-8");

		std::string mime = m_mimedict.get( extension , defaultType ) ;
		res.setHeader(key,mime);
		onion_response_write_headers(res.c_handler());// missing in cpp bindings?
		//res.writeHeaders();//this was added by me...

		try{
			while (std::getline(file, line)) {
				res.write( line.c_str(), line.size() );
				res.write("\n", 1 );
			}
		}//catch ( const boost::iobase::failure &ex )
		catch ( const std::exception & ex ){
			std::cerr << "Can not read " << filename << std::endl;
			res.write( ErrReadFailed.c_str(), ErrReadFailed.size());
		}
	}else{
		res.write( ErrNotFound.c_str(), ErrNotFound.size());
	}

	return OCS_PROCESSED;
}

/*
 Replace some template variables (filename of last config) call index_html_template
*/
onion_connection_status OnionServer::index_html( Onion::Request &req, Onion::Response &res)
{
	/* Issue note: The following cause double free of mem because
	 * onion_dict_free will called twice: in index_html_template and deconstructor.
	 * Onion::Dict d;
	 std::string key("LAST_SETTING_FILENAME");
	 d.add(key,m_settingKinect.m_configFilename,0);
	 return index_html_template(d.c_handler(), req.c_handler(), res.c_handler() );

	 => Thus, use pointer, but do not free here.
	 */
	onion_dict *d=onion_dict_new();//will free'd in template call
	onion_dict_add( d, "LAST_SETTING_FILENAME",
			m_settingKinect.m_configFilename.c_str(), 0);

	return index_html_template(d, req.c_handler(), res.c_handler() );
}


/*
 Replace some template variables and send kinect_settings.js
 The elegant template approach was disabled due the lack of
 template type detection. In this variant all quotes will be
 replaced by its html special char encoding (&quot;). This destroys 
 java script variables.
*/
/*
onion_connection_status OnionServer::getSettingKinectWrapped(
		Onion::Request &req, Onion::Response &res)
{
	onion_dict *d=onion_dict_new();//will free'd in template call
	onion_dict_add( d, "ONION_JSON_KINECT",
			m_settingKinect.getConfig(), 0);
	return kinect_settings_js_template(d, req.c_handler(), res.c_handler());
}*/

/* Like 'search_file' */
onion_connection_status OnionServer::getSettingKinectWrapped(
		Onion::Request &req, Onion::Response &res)
{
	const char* path = onion_request_get_fullpath( req.c_handler() );
#ifdef VERBOSE
	printf("Request of %s.\n",path);
#endif
	std::string filename("./html/");
	filename.append(path);

	std::ifstream file(filename.c_str());
	std::string line;

	if( file.is_open()){

		/* Create header with mime type and charset information for several file extensions.
		 * This is just a workaround. There should be an automatic mechanicm
		 * in libonion. */
		int periodPos = filename.find_last_of('.');
		std::string extension = filename.substr(periodPos+1);
		std::string key("Content-Type");
		std::string defaultType("text/html; charset: utf-8");

		std::string mime = m_mimedict.get( extension , defaultType ) ;
		res.setHeader(key,mime);
		onion_response_write_headers(res.c_handler());// missing in cpp bindings?
		//res.writeHeaders();//this was added by me...

		try{
			/*
			res.write("json_kinect = ", 14);
			const char* kinect = m_settingKinect.getConfig(true);
			size_t len = strlen( kinect );
			res.write(kinect, (int) len );
			res.write(";\n", 2 );
			*/

			while (std::getline(file, line)) {
				res.write( line.c_str(), line.size() );
				res.write("\n", 1 );
			}
		}//catch ( const boost::iobase::failure &ex )
		catch ( const std::exception & ex ){
			std::cerr << "Can not read " << filename << std::endl;
			res.write( ErrReadFailed.c_str(), ErrReadFailed.size());
		}
	}else{
		res.write( ErrNotFound.c_str(), ErrNotFound.size());
	}

	return OCS_PROCESSED;
}


/*+++++++++++++ OnionServer-Class ++++++++++++++++++ */
OnionServer::OnionServer(SettingKinect &settingKinect ):
#ifndef DETACH_MANUAL
	m_onion( O_THREADED|O_DETACH_LISTEN|O_NO_SIGTERM),
#else
	m_onion( O_ONE_LOOP),
#endif
	m_url(m_onion),
	m_mimedict(),
	m_mimes(),
	//m_urls(),
	m_view(m_settingKinect.m_view),
	m_settingKinect(settingKinect) {
		//m_onion.setTimeout(5000);

		// Store used mime types
		m_mimes.push_back("html");
		m_mimes.push_back("text/html; charset: utf-8");
		m_mimes.push_back("css");
		m_mimes.push_back("text/css; charset: utf-8"); 
		m_mimes.push_back("js");
		m_mimes.push_back("application/javascript; charset: utf-8");
		m_mimes.push_back("png");
		m_mimes.push_back("image/png");
		m_mimes.push_back("jpg");
		m_mimes.push_back("image/jpeg");

		//Set mime types dict
		m_mimedict.add( m_mimes[0], m_mimes[1], 0);
		m_mimedict.add( m_mimes[2], m_mimes[3], 0);
		m_mimedict.add( m_mimes[4], m_mimes[5], 0);
		m_mimedict.add( m_mimes[6], m_mimes[7], 0);
		m_mimedict.add( m_mimes[8], m_mimes[9], 0);


		//add default signal handler.
		updateSignal.connect(
				boost::bind(&OnionServer::updateWebserver,this, _1, _2, _3)
				);
		//add signal handler of m_settingKinect
		updateSignal.connect(
				boost::bind(&SettingKinect::webserverUpdateConfig,&m_settingKinect, _1, _2, _3)
				);
	}

void OnionServer::setupUrls() {
	m_url.add<OnionServer>("", this, &OnionServer::index_html );
	m_url.add<OnionServer>("index.html", this, &OnionServer::index_html );

	/** Dynamic content **/
	/* Send data */
	m_url.add<OnionServer>("kinect_settings.js", this, &OnionServer::getSettingKinectWrapped );
	m_url.add<OnionServer>("settings", this, &OnionServer::getSettingKinect );
	//m_url.add<OnionServer>("messages", this, &OnionServer::getPrinterMessages );
	m_url.add<OnionServer>("preview.image", this, &OnionServer::preview );
#ifdef WEB_DISPLAY_USES_JPEG
	m_url.add<OnionServer>("preview.jpg", this, &OnionServer::preview ); // Redundant
#else
	m_url.add<OnionServer>("preview.png", this, &OnionServer::preview ); // Redundant
#endif

	/* Recive data */
	m_url.add<OnionServer>("update", this, &OnionServer::updateData );

	//	m_url.add<OnionServer>("", this, &OnionServer::getJobFolderWrapped );
	//	m_url.add<OnionServer>("", this, &OnionServer::getJobFolder );

	/** Static content **/
	/* Send data, should be the last added case. */
	m_url.add<OnionServer>("^.*$", this, &OnionServer::search_file );
}

int OnionServer::start_server() {

	std::string host(m_settingKinect.getString("host"));
	std::string port(m_settingKinect.getString("port"));

	m_onion.setHostname(host);
	m_onion.setPort(port);

  std::cout << "KinectGrid server url: http://" << "localhost" << ":" << port << std::endl;
	setupUrls();

	//start loop as thread  (O_DETACH_LISTEN flag is set.)
	m_onion.listen();
#ifndef DETACH_MANUAL
	return 0;
#else
	return pthread_create( &m_pthread, NULL, &start_myonion_server, &m_onion);
#endif
}

int OnionServer::stop_server()
{
	m_onion.listenStop();
#ifndef DETACH_MANUAL
	return 0;
#else
	int i = pthread_join( m_pthread, NULL);//wait till loop ends
	return i;
#endif
}

/* The user can select a new view over the webinterface (thread A), but this
 * thread can not set the view variable (mainly used in thread B) of the setting
 * struct without blocking for a unknown amount of time.
 * Thus, the webinterface caches new values locally. This will be read by thread B 
 * later.
 * If no new view was selected, the input value will be reflected. 
 */
View OnionServer::getView(View in){
	if(m_view < 0) return in;
	View ret = m_view;
	m_view = VIEW_UNKNOWN;
	return ret;
};

/* return value marks, if reply string contains data which should
 * return to the web client:
 * -3: No data written into reply. Input generate state which require reloading of web page.
 * -2: No data written into reply, but input processed successful.
 * -1: No data written into reply. Input has generate error. (Currently not used.)
 *  0: data written into reply
 *  1: data written, but error occours.
 *  2: two signals wrote data. The output is likely unuseable
 
Old approach was:
Signal return value is OR-Combination of signal handles.
    true: request handling succesful. 
		false: no handler deals with the request.
 */
int OnionServer::updateWebserver(
		Onion::Request *preq, int actionid, Onion::Response *pres ){
	VPRINT("Http action id: %i \n", actionid);

	switch(actionid){
		case HTTP_ACTION_SEND_COMMAND:
			{ /* Command Message, unused */
				const char* json_str = onion_request_get_post(preq->c_handler(), "cmd");
				std::string reply;

				if( json_str != NULL){
					Messages &q = m_settingKinect.m_queues;
					std::string cmd(json_str);
					q.add_command(cmd);	
					reply = "ok";
				}else{
					reply = "missing post variable 'cmd'";
				}

				pres->write(reply.c_str(), reply.size() );
				return 0;
			}
			break;

		case HTTP_ACTION_RESET_CONFIG:{  //reset config values to defaults.
						 m_settingKinect.loadConfigFile("");
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_QUIT_PROGRAM:{  //quit programm
						 std::string reply("quit");
						 pres->write(reply.c_str(), reply.size() );
						 VPRINT("Quitting...\n");
						 m_settingKinect.lock();
						 //m_settingKinect.m_die = true;
						 m_settingKinect.setMode(QUIT);
						 m_settingKinect.unlock();
						 return 0;
					 }
					 break;
		case HTTP_ACTION_LOAD_MASKS:{  //load masks
						 m_settingKinect.setMode(LOAD_MASKS);
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_SAVE_MASKS:{ //save masks
						 m_settingKinect.setMode(SAVE_MASKS);
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_SELECT_VIEW:{ //select view
						 //m_view = atoi( onion_request_get_queryd(req,"view","0") );
						 m_view = (View) atoi( onion_request_get_post(preq->c_handler(),"view") );
						 VPRINT("Set view to %i.\n",(int)m_view);
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_REPOKE:{ //repoke
						 VPRINT("Repoke\n");
						 m_settingKinect.setMode(REPOKE_DETECTION);
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_SET_AREA_DETECTION:{ // area detection
						 int start = atoi( onion_request_get_post(preq->c_handler(),"start") );
						 if( start == 1)
							 m_settingKinect.setMode(AREA_DETECTION_START);
						 else{
							 m_settingKinect.setMode(AREA_DETECTION_END);
						 }
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_SAVE_CONFIG:{
						 const char* configFilename = onion_request_get_post(preq->c_handler(), "configFilename");
						 VPRINT("Save new settingKinectGrid: %s\n",configFilename);
						 if( check_configFilename(configFilename) ){
							 m_settingKinect.saveConfigFile(configFilename);
							 //m_settingKinect.setString("lastSetting",configFilename);
							 //m_settingKinect.saveConfigFile("settingKinectGrid.ini");
						 }else{
							 VPRINT("Filename not allowed\n");
						 }
						 std::string reply("ok");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
		case HTTP_ACTION_LOAD_CONFIG:{
						 const char* configFilename = onion_request_get_post(preq->c_handler(), "configFilename");
						 VPRINT("Load new settingKinectGrid: %s\n",configFilename);
						 if( check_configFilename(configFilename) ){
							 m_settingKinect.loadConfigFile(configFilename);
						 }else{
							 printf("Filename not allowed\n");
						 }
						 /* force reload of website */
						 std::string reply("reload");
						 pres->write(reply.c_str(), reply.size() );
						 return 0;
					 }
					 break;
					 //case 0: // this case will be handled in webserverUpdateConfig
		default:{
						}
						break;
	}

	return -3;
}



