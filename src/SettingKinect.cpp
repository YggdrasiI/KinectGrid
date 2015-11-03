#include <vector>
#include "SettingKinect.h"
#include "OnionServer.h"

using namespace std;

SettingKinect::SettingKinect(bool withKinect) :
	JsonConfig(),
	m_mode(HAND_DETECTION),
	m_view(VIEW_NONE),
	m_mode_mutex(),
	m_queues(),
	m_host(),
	m_port(),
	m_configFilename(),
	m_tuio2Dcur_host(),
	m_tuio25Dblb_host(),
	m_displayMode(DISPLAY_MODE_NONE),
	m_withKinect(withKinect)
{
	loadDefaults();
}

SettingKinect::~SettingKinect(){
}

void SettingKinect::setMode(FunctionMode mode){
	m_mode_mutex.lock();
	m_mode = mode;
	m_mode_mutex.unlock();
}

FunctionMode SettingKinect::getModeAndLock(){
	m_mode_mutex.lock();
	return m_mode;
}

void SettingKinect::unlockMode(FunctionMode mode){
	m_mode = mode;
	m_mode_mutex.unlock();
}

/*
 * Generate json struct of properties. Use the subnode 'html'
 * for values which can be modified on the web interface.
 */
cJSON *SettingKinect::genJson()
{
	cJSON *root = cJSON_CreateObject();	
	/* Kind only used to distinct different json structs. */
	cJSON_AddItemToObject(root, "kind", cJSON_CreateString("kinectSettings"));

	cJSON_AddItemToObject(root, "host", cJSON_CreateString(m_host.c_str() ));
	cJSON_AddItemToObject(root, "port", cJSON_CreateString(m_port.c_str() ));
	cJSON_AddItemToObject(root, "tuio2Dcur_host", cJSON_CreateString(m_tuio2Dcur_host.c_str()));
	cJSON_AddItemToObject(root, "tuio25Dblb_host", cJSON_CreateString(m_tuio25Dblb_host.c_str()));
	cJSON_AddItemToObject(root, "tuio2Dcur_port", cJSON_CreateNumber(m_tuio2Dcur_port));
	cJSON_AddItemToObject(root, "tuio25Dblb_port", cJSON_CreateNumber(m_tuio25Dblb_port));
	cJSON_AddItemToObject(root, "masks", cJSON_CreateString(m_masks.c_str() ));
	cJSON_AddItemToObject(root, "display", cJSON_CreateNumber(m_displayMode));

	/* Sub node. This values will transmitted to the web interface */
	cJSON *html = cJSON_CreateArray();	

	cJSON_AddItemToArray(html, jsonDoubleField("kinectMotorAngle",
				m_kinectProp.kinectMotorAngle,-16,16,5) );
	cJSON_AddItemToArray(html, jsonIntField("minDepth",
				m_kinectProp.minDepth,0,2047,100) );
	cJSON_AddItemToArray(html, jsonIntField("maxDepth",
				m_kinectProp.maxDepth,0,2047,100) );
	cJSON_AddItemToArray(html, jsonIntField("minBlobArea",
				m_kinectProp.minBlobArea,16,4096*4,100) );
	cJSON_AddItemToArray(html, jsonIntField("maxBlobArea",
				m_kinectProp.maxBlobArea,16,4096*8,250) );
	cJSON_AddItemToArray(html, jsonIntField("marginLeft",
				m_kinectProp.marginLeft,0,KRES_X-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginRight",
				m_kinectProp.marginRight,0,KRES_X-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginTop",
				m_kinectProp.marginTop,0,KRES_Y-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginBottom",
				m_kinectProp.marginBottom,0,KRES_Y-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginFront",
				m_kinectProp.marginFront,0,255,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginBack",
				m_kinectProp.marginBack,0,255,100) );
	cJSON_AddItemToArray(html, jsonCheckbox("TUIO_2Dcur",
				m_tuioProtocols[0]) );
	cJSON_AddItemToArray(html, jsonCheckbox("TUIO_25Dblb",
				m_tuioProtocols[1]) );
	cJSON_AddItemToArray(html, jsonCheckbox("areaThresh",
				m_kinectProp.areaThresh) );
	cJSON_AddItemToArray(html, jsonCheckbox("directFiltering",
				m_kinectProp.directFiltering) );
	cJSON_AddItemToArray(html, jsonCheckbox("clipping",
				m_kinectProp.clipping) );

	// This field we be ignored if the user changes them on the website.
	cJSON_AddItemToArray(html, jsonStateField("viewState",m_view,"token","token") );
	cJSON_AddItemToArray(html, jsonStateField("modeState",m_mode,"token","token") );
	cJSON_AddItemToArray(html, jsonStateField("tuio2Dcur_host",m_tuio2Dcur_host) );
	cJSON_AddItemToArray(html, jsonStateField("tuio25Dblb_host",m_tuio25Dblb_host) );
	cJSON_AddItemToArray(html, jsonStateField("tuio2Dcur_port",m_tuio2Dcur_port) );
	cJSON_AddItemToArray(html, jsonStateField("tuio25Dblb_port",m_tuio25Dblb_port) );
	cJSON_AddItemToArray(html, jsonStateField("masks",m_masks) );

	cJSON_AddItemToObject(root, "html", html);

	
	cJSON* areas = cJSON_CreateArray();	
	for(int i=0; i<m_areas.size(); i++){
		cJSON_AddItemToArray(areas, jsonArea(m_areas[i].id,m_areas[i].repoke_x,m_areas[i].repoke_y,m_areas[i].depth) );
	}
	cJSON_AddItemToObject(root, "areas", areas);

	return root;
};

void SettingKinect::loadDefaults()
{
	m_host = "0.0.0.0";
	m_port = "8080";
	m_tuio2Dcur_host = "127.0.0.1"; 
	m_tuio25Dblb_host = "127.0.0.1"; 
	m_tuio2Dcur_port = 3333;
	m_tuio25Dblb_port = 3335;
	m_masks = "masks"; 
	m_tuioProtocols[0] = false;
	m_tuioProtocols[1] = true;
	m_kinectProp.kinectMotorAngle=0.0;
	m_kinectProp.minDepth=0;
	m_kinectProp.maxDepth=2047;
	m_kinectProp.minBlobArea=256;
	m_kinectProp.maxBlobArea=3000;
	m_kinectProp.marginLeft=0;
	m_kinectProp.marginRight=0;
	m_kinectProp.marginTop=0;
	m_kinectProp.marginBottom=0;
	m_kinectProp.marginFront=0;
	m_kinectProp.marginBack=0;
	m_kinectProp.areaThresh = false;
	m_kinectProp.directFiltering = false;
	m_kinectProp.clipping = true;
};

/*
 * replaces |=YES with |=XYZ to extend changes flag.
 * It's could be useful to detect special updates, conflicts...
 */
int SettingKinect::update(cJSON *jsonNew, cJSON *jsonOld, int changes){
	cJSON *nhtml = cJSON_GetObjectItem(jsonNew,"html");
	cJSON *ohtml = jsonOld==NULL?NULL:cJSON_GetObjectItem(jsonOld,"html");

	lock();

	/*load values outside of the html node. This values should only
	* read from config files.
	*/
	if( changes & CONFIG ){
		m_host = JsonConfig::getString(jsonNew,"host");
		m_port = JsonConfig::getString(jsonNew,"port");
		m_tuio2Dcur_host = JsonConfig::getString(jsonNew,"tuio2Dcur_host");
		m_tuio25Dblb_host = JsonConfig::getString(jsonNew,"tuio25Dblb_host");
		m_tuio2Dcur_port = JsonConfig::getNumber(jsonNew,"tuio2Dcur_port");
		m_tuio25Dblb_port = JsonConfig::getNumber(jsonNew,"tuio25Dblb_port");
		m_masks = JsonConfig::getString(jsonNew,"masks");
	}

	if( nhtml != NULL){

		if( JsonConfig::update(nhtml,ohtml,"kinectMotorAngle",&m_kinectProp.kinectMotorAngle) ) changes|=MOTOR;
		if( JsonConfig::update(nhtml,ohtml,"minDepth",&m_kinectProp.minDepth)
				+ JsonConfig::update(nhtml,ohtml,"maxDepth",&m_kinectProp.maxDepth) ){
			changes|=MARGIN|FRONT_MASK;
			m_kinectProp.maxDepth = max(m_kinectProp.minDepth+2,m_kinectProp.maxDepth);

			//update rangeMap
			/* Map [0,2048]⌋ ⊇ [minDepth, maxDepth] linear onto [255,0] via
			 * f(x) = alpha * x + beta
			 * 
			 */
			int alphaEnumerator, alphaDenominator, beta;
			alphaEnumerator = 0-255;
			alphaDenominator = m_kinectProp.maxDepth - m_kinectProp.minDepth;
			beta = (255*m_kinectProp.maxDepth - 0*m_kinectProp.minDepth) / ( m_kinectProp.maxDepth - m_kinectProp.minDepth );

			for(int i=0; i<2048; ++i){
				int tmp  = (i*alphaEnumerator)/alphaDenominator + beta;
				m_rangeMap[i] = (0>tmp)?0:((tmp<255)?tmp:255);
				//printf("r[%i] = %i\n", i, m_rangeMap[i]);
			}
			m_rangeMap[2047/*FREENECT_DEPTH_RAW_NO_VALUE*/] = 0;

			// Map values below minimal distance to zero
			for( int i=m_kinectProp.minDepth-1; i; --i){
				m_rangeMap[i] = 0;
			}

		}

		JsonConfig::update(nhtml,ohtml,"minBlobArea",&m_kinectProp.minBlobArea);
		JsonConfig::update(nhtml,ohtml,"maxBlobArea",&m_kinectProp.maxBlobArea);
		if( JsonConfig::update(nhtml,ohtml,"marginLeft",&m_kinectProp.marginLeft) ) changes|=MARGIN;
		if( JsonConfig::update(nhtml,ohtml,"marginRight",&m_kinectProp.marginRight) ) changes|=MARGIN;
		if( JsonConfig::update(nhtml,ohtml,"marginTop",&m_kinectProp.marginTop) ) changes|=MARGIN;
		if( JsonConfig::update(nhtml,ohtml,"marginBottom",&m_kinectProp.marginBottom) ) changes|=MARGIN;
		if( JsonConfig::update(nhtml,ohtml,"marginFront",&m_kinectProp.marginFront) ) changes|=MARGIN|FRONT_MASK;
		if( JsonConfig::update(nhtml,ohtml,"marginBack",&m_kinectProp.marginBack) ) changes|=BACK_MASK;

		if( JsonConfig::updateCheckbox(nhtml,ohtml,"TUIO_2Dcur",&m_tuioProtocols[0]) ) changes|=TUIO_PROTOCOL;
		if( JsonConfig::updateCheckbox(nhtml,ohtml,"TUIO_25Dblb",&m_tuioProtocols[1]) ) changes|=TUIO_PROTOCOL;

		if( JsonConfig::updateCheckbox(nhtml,ohtml,"areaThresh",&m_kinectProp.areaThresh) ) changes|=BACK_MASK ; 
		if( JsonConfig::updateCheckbox(nhtml,ohtml,"directFiltering",&m_kinectProp.directFiltering) ) changes|=BACK_MASK; 
		if( JsonConfig::updateCheckbox(nhtml,ohtml,"clipping",&m_kinectProp.clipping) ){
			changes|=CLIPPING; 
		}
		//update region of interest
		int w,h,x,y;
		x = max(m_kinectProp.marginLeft,0);
		y = max(m_kinectProp.marginTop,0);
		w = max(KRES_X-m_kinectProp.marginLeft-m_kinectProp.marginRight,0);
		h = max(KRES_Y-m_kinectProp.marginTop-m_kinectProp.marginBottom,0);
		updateRoi(x,y,w,h);

		// fill m_area, if empty. (if-criteria should improved?!)
		if( m_areas.size() == 0){
			printf("Init m_areas\n");
			cJSON* areas = cJSON_GetObjectItem(jsonNew,"areas");
			if( areas != NULL ){
				int na =  cJSON_GetArraySize(areas);
				printf("Init m_areas(2)\n");
				cJSON* area;
				for(int i=0;i<na;i++){
					printf("get %ith area.\n",i+1);
					area = cJSON_GetArrayItem(areas, i);
					Area a;
					a.id = cJSON_GetObjectItem(area,"id")->valueint;
					a.repoke_x =  (float)cJSON_GetObjectItem(area,"x")->valuedouble;
					a.repoke_y =  (float)cJSON_GetObjectItem(area,"y")->valuedouble;
					a.depth =  (float)cJSON_GetObjectItem(area,"depth")->valuedouble;
					m_areas.push_back(a);
				}
			}
		}

		//call signal
		printf("Changes: %i\n",changes);
	  //updateSig(this,changes);
	}

	unlock();

	//call update signal
	updateSettings(changes);	

	return changes!=NO?1:0;
}

/* Update of val without argument checking. */
bool SettingKinect::updateState(cJSON *jsonNew, cJSON *jsonOld,const char* id, int* val){
	double tmp=*val;
	bool ret = updateState(jsonNew,jsonOld,id,&tmp);
	*val = (int)tmp;
	return ret;
}
bool SettingKinect::updateState(cJSON *jsonNew, cJSON *jsonOld,const char* id, double* val){
	cJSON *ntmp = getArrayEntry(jsonNew,id);
	cJSON *otmp;
	bool ret(false);
	//VPRINT("update of %s:",id);				
	double nval=0.0, oval=*val;
	if( jsonOld != NULL && NULL != (otmp=getArrayEntry(jsonOld,id)) ){
		oval = getNumber(otmp,"val");
		nval = getNumber(ntmp,"val");
		if(oval!=nval){
			/* Attention. The case 'oval!=*val' indicates changes of this property
			 * by an other thread/operation. nval OVERWRITE *val. This could
			 * be problematic in some special cases. */
			*val = nval;
			ret=true;
		}
	}else if( ntmp != NULL){
		nval = getNumber(ntmp,"val");
		*val = nval;
		ret = true;
	}
	//VPRINT(" %f\n",nval);				
	return ret;
}

bool SettingKinect::updateRoi(int x, int y, int width, int height){
	if( x<0 || y<0 || x+width>KRES_X || y+height>KRES_Y){
		return false;
	}
	m_kinectProp.roi.x = x;
	m_kinectProp.roi.y = y;
	m_kinectProp.roi.width = width;
	m_kinectProp.roi.height = height;
	VPRINT("Roi: (%i,%i,%i,%i)\n",m_kinectProp.roi.x,m_kinectProp.roi.y,m_kinectProp.roi.width,m_kinectProp.roi.height);
}

bool SettingKinect::webserverUpdateConfig(Onion::Request *preq, int actionid, Onion::Response *pres){
	if( actionid == HTTP_ACTION_UPDATE_CONFIG ){
		VPRINT("update kinectSettings values\n");
		const char* json_str = onion_request_get_post(preq->c_handler(), "kinectSettings");
		if( json_str != NULL){
			setConfig(json_str, WEB_INTERFACE|PARSE_AGAIN);
			//hm, send update signal here with some flags which mark changes?
		}
		std::string reply = "ok";
		pres->write( reply.c_str(), reply.size() ); 
		return true;
	}
return false;
}


void SettingKinect::setAreas(std::vector<Area> &new_areas){

	//m_areas.clear();//redundant
	m_areas = new_areas;//copy vector 

	//update area field in settingKinect
	//cJSON* oareas = cJSON_GetObjectItem(m_pjson_root,"areas");  
	cJSON* areas = cJSON_CreateArray();	

	for(int i=0; i<m_areas.size(); i++){
		cJSON_AddItemToArray(areas, jsonArea(m_areas[i].id,m_areas[i].repoke_x,m_areas[i].repoke_y,m_areas[i].depth) );
	}

	m_json_mutex.lock();
	cJSON_ReplaceItemInObject(m_pjson_root, "areas", areas);
	m_json_mutex.unlock();
	//cJSON_Delete( );
	//printf("Json updated?!\n%s", getConfig());
}
