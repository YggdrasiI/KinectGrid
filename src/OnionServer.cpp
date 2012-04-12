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
#include "OnionServer.h"

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
int index_html_template(void *, onion_request *req, onion_response *res);
int mmtt_script_js_template(void *, onion_request *req, onion_response *res);
int mmtt_settings_js_template(void *p, onion_request *req, onion_response *res);
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
int insert_json(void *, onion_request *req, onion_response *res, void* data, void* datafree)
{
onion_dict *d=onion_dict_new();
onion_dict_add(d, "ONION_JSON_KINECT",((JsonConfig*)data)->getConfig(),0);
//onion_dict_add(d, "user", user, OD_DICT|OD_FREE_VALUE);

return mmtt_settings_js_template(d, req, res);
}

/*+++++++++++++ OnionServer-Class ++++++++++++++++++ */
int OnionServer::start_server()
{
	onion_url *url=onion_root_url(m_ponion);

	onion_set_hostname(m_ponion, "0.0.0.0"); // Force ipv4.
	onion_set_port(m_ponion, "8080");
	onion_url_add_with_data(url, "mmtt_settings.js", (void*)insert_json, m_psettingKinect, NULL);
	onion_url_add(url, "mmtt_script.js", (void*)mmtt_script_js_template);
	onion_url_add(url, "index.html", (void*)index_html_template);
	onion_url_add(url, "", (void*)index_html_template);
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



