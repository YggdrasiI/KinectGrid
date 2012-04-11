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
int mandelbrot(void *p, onion_request *req, onion_response *res){
	int width=atoi(onion_request_get_queryd(req,"width","256"));
	int height=atoi(onion_request_get_queryd(req,"height","256"));
	double left=atof(onion_request_get_queryd(req,"X","-2"));
	
	unsigned char *image=new unsigned char[width*height];
	unsigned char *imagep=image;
 	
	onion_png_response(image, 1, width, height, res);
	delete image;
	return OCS_PROCESSED;
}

int mmtt_settings_js_template(void *p, onion_request *req, onion_response *res){
	return OCS_PROCESSED;
}



// This has to be extern, as we are compiling C++
extern "C"{
int index_html_template(void *, onion_request *req, onion_response *res);
int mmtt_script_js_template(void *, onion_request *req, onion_response *res);
}

int data(void *, onion_request *req, onion_response *res){
onion_dict *d=onion_dict_new();
onion_dict *birth=onion_dict_new();
onion_dict *user=onion_dict_new();

onion_dict_add(birth, "year","1980",0);

onion_dict_add(user, "birth", birth, OD_DICT|OD_FREE_VALUE); onion_dict_add(user, "name","David Moreno",0);

onion_dict_add(d, "user", user, OD_DICT|OD_FREE_VALUE); onion_dict_add(d, "title","My title",0);

return index_html_template(d, req, res);
}

/*+++++++++++++ OnionServer-Class ++++++++++++++++++ */
int OnionServer::start_server(){
	onion_url *url=onion_root_url(m_ponion);

	onion_set_hostname(m_ponion, "0.0.0.0"); // Force ipv4.
	onion_set_port(m_ponion, "8080");
	onion_url_add(url, "mmtt_settings.js", (void*)data);
	onion_url_add(url, "mmtt_script.js", (void*)mmtt_script_js_template);
	onion_url_add(url, "index.html", (void*)index_html_template);
	onion_url_add(url, "", (void*)index_html_template);

	//start loop as thread
	return pthread_create( &m_pthread, NULL, &start_myonion_server, m_ponion);	
}

int OnionServer::stop_server(){
	onion_listen_stop(m_ponion);//stop loop
	int i = pthread_join( m_pthread, NULL);//wait till loop ends
	onion_free(m_ponion);
	return i;
}
