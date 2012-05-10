/*
	Onion HTTP server library
	Copyright (C) 2010 David Moreno Montero

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Affero General Public License as
	published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Affero General Public License for more details.

	You should have received a copy of the GNU Affero General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
	*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <regex.h>
#include "OnionServer.h"


int check_filename(const char *filename){
	regex_t regex;
	int reti, ret;
	char msgbuf[100];

	/* Compile regular expression */
	reti = regcomp(&regex, "^[[:alnum:]]*\\.json$", 0);
	if( reti ){ fprintf(stderr, "Could not compile regex\n"); return -1; }

	/* Execute regular expression */
	reti = regexec(&regex, filename, 0, NULL, 0);
	if( !reti ){
		ret= 1;
	}else if( reti == REG_NOMATCH ){
		ret= 0;
	}else{
		regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		ret= 0;
	}

	/* Free compiled regular expression if you want to use the regex_t again */
	regfree(&regex);

	return ret;
}
/**
 * @short Calculates the given mandelbrot, and returns the PNG image
 * 
 * It can receive several query parameters, but all are optional:
 * 
 * * X, Y -- Top left complex area position
 * * W, H -- Width and Height of the complex area to show
 * * width, height -- Image size
 */
int mandelbrot(void *p, onion_request *req, onion_response *res)
{
	int width=atoi(onion_request_get_queryd(req,"width","256"));
	int height=atoi(onion_request_get_queryd(req,"height","256"));
	double left=atof(onion_request_get_queryd(req,"X","-2"));
	
	unsigned char *image=new unsigned char[width*height];
	unsigned char *imagep=image;
 	
	onion_png_response(image, 1, width, height, res);
	delete image;
	return OCS_PROCESSED;
}

// This has to be extern, as we are compiling C++
extern "C"{
int index_html_template(void *p, onion_request *req, onion_response *res);
int mmtt_script_js_template(void *p, onion_request *req, onion_response *res);
int mmtt_settings_js_template(void *p, onion_request *req, onion_response *res);
}

/*
 Check post values and then return template of index.html.
 (Or use *p for other callbacks (not implemented))
*/
int checkFormularValues(void *p, onion_request *req, onion_response *res){
	int ok = ((OnionServer*)p)->updateSetting(req,res);
	if( ok != 0){
		onion_response_set_length(res, 6);
		onion_response_write(res, "reload", 6); 
	}else{
		onion_response_set_length(res, 2);
		onion_response_write(res, "Ok", 2); 
	}
	return OCS_PROCESSED;
}

/*
 Return raw file if found. Security risk?! Check of filename/path required?!
*/
int search_file(onion_dict *context, onion_request *req, onion_response *res){
	//const char* path = onion_request_get_path(req);//empty?!
	const char* path = onion_request_get_fullpath(req);
	printf("Request of %s %i.\n",path, strlen(path));
	char filename[strlen(path)+8];
	//sprintf(filename,"./%s",path);
	sprintf(filename,"./html/%s",path);

		//read file 
	if( FILE *f=fopen(filename,"rb") ){
		fseek(f,0,SEEK_END);
		long len=ftell(f);
		fseek(f,0,SEEK_SET);
		char *data=(char*)malloc(len+1);
		fread(data,1,len,f);
		fclose(f);

		if (context) onion_dict_add(context, "LANG", onion_request_get_language_code(req), OD_FREE_VALUE);
		onion_response_set_length(res, len);
		onion_response_write(res, data, len); 
		if (context) onion_dict_free(context);

		free(data);
	}else{
		onion_response_set_length(res, 24);
		onion_response_write(res, "<h1>File not found</h1>", 24); 
	}
	return OCS_PROCESSED;
}

/*
 Replace some template variables and send mmtt_settings.js
*/
int insert_json(void *data, onion_request *req, onion_response *res, void* foo, void* datafree)
{
 //	printf("Pointer in callback: %p %p %p)\n",data,p,datafree);
onion_dict *d=onion_dict_new();
if( data != NULL){
	onion_dict_add(d, "ONION_JSON_KINECT",((JsonConfig*)data)->getConfig(),0);
}
//onion_dict_add(d, "user", user, OD_DICT|OD_FREE_VALUE);

return mmtt_settings_js_template(d, req, res);
}

/*
 Replace some template variables (filename of last config) call index_html_template
*/
int index_html(void *data, onion_request *req, onion_response *res, void* foo, void* datafree)
{
 //	printf("Pointer in callback: %p %p %p)\n",data,p,datafree);
onion_dict *d=onion_dict_new();
if( data != NULL){
	onion_dict_add(d, "LAST_SETTING_FILENAME",((JsonConfig*)data)->getString("lastSetting"),0);
}

return index_html_template(d, req, res);
}

/*+++++++++++++ OnionServer-Class ++++++++++++++++++ */
int OnionServer::start_server()
{
	onion_url *url=onion_root_url(m_ponion);

	const char *host, *port;
	if( m_psettingMMTT != NULL){
		host = m_psettingMMTT->getString("host");
		port = m_psettingMMTT->getString("port");
	}else{
		host = "0.0.0.0";
		port = "8080";
	}

	onion_set_hostname(m_ponion, host); // Force ipv4.
	onion_set_port(m_ponion, port);
	onion_url_add_with_data(url, "mmtt_settings.js", (void*)insert_json, m_psettingKinect, NULL);
	onion_url_add_with_data(url, "index.html", (void*)index_html, m_psettingMMTT, NULL);
	onion_url_add_with_data(url, "", (void*)index_html, m_psettingMMTT, NULL);
	//onion_url_add_with_data(url, "index.html", (void*)checkFormularValues, this, NULL);
	//onion_url_add_with_data(url, "", (void*)checkFormularValues, this, NULL);
	onion_url_add_with_data(url, "json", (void*)checkFormularValues, this, NULL);
	onion_url_add(url, "^.*$", (void*)search_file);

	//start loop as thread
	return pthread_create( &m_pthread, NULL, &start_myonion_server, m_ponion);	
}

int OnionServer::stop_server()
{
	onion_listen_stop(m_ponion);//stop loop
	int i = pthread_join( m_pthread, NULL);//wait till loop ends
	onion_free(m_ponion);
	return i;
}

int OnionServer::updateSetting(onion_request *req, onion_response *res){
	int actionid = atoi( onion_request_get_queryd(req,"actionid","0") );
	switch(actionid){
		case 5:{ //select view
							//m_view = atoi( onion_request_get_queryd(req,"view","-1") );
							m_view = atoi( onion_request_get_post(req,"view") );
						 printf("Set view to %i.\n",m_view);
					 }
					 break;
		case 4:{ //repoke
						 printf("Repoke\n");
								m_psettingMMTT->setMode(REPOKE_DETECTION);
					 }
					 break;
		case 3:{ // area detection
							int start = atoi( onion_request_get_queryd(req,"start","1") );
							if( start == 1)
								m_psettingMMTT->setMode(AREA_DETECTION_START);
							else{
								m_psettingMMTT->setMode(AREA_DETECTION_END);
							}
					 }
			break;
		case 2:{
						 const char* filename = onion_request_get_post(req,"filename");
						 printf("Save new settingMMTT: %s\n",filename);
						 if( check_filename(filename ) == 1){
							 m_psettingKinect->saveConfigFile(filename);
							 m_psettingMMTT->setString("lastSetting",filename);
							 m_psettingMMTT->saveConfigFile("settingMMTT.ini");
						 }else{
						 	printf("Filename not allowed\n");
						 }
						 /* force reload of website */
						 return 0;
					 }
			break;
		case 1:{
						 const char* filename = onion_request_get_post(req,"filename");
						 printf("Load new settingMMTT: %s\n",filename);
						 if( check_filename(filename ) == 1){
							 m_psettingKinect->loadConfigFile(filename);
						 }else{
							 printf("Filename not allowed\n");
						 }
						 return -1;
					 }
			break;
		case 0:
		default:{
							printf("update settingKinect values\n");
							const char* json_str = onion_request_get_post(req,"settingKinect");
							if( json_str != NULL){
								//printf("Get new settingKinect: %s\n",json_str);
								m_psettingKinect->setConfig(json_str, NO);
							}else{
								return -1;
							}
						}
			break;
	}
	return 0; 
}





