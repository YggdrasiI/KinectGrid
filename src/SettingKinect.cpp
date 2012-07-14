#include "SettingKinect.h"


/*
 * Special properties. This values can modified with the web interface.
 * I.e. angle of kinect, nmbr of areas, position of areas, minimal blob size.
 */
cJSON* SettingKinect::loadDefaults()
{
	cJSON* root = cJSON_CreateObject();	
	cJSON_AddStringToObject(root, "kind", "settingKinect");
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("form"));

	cJSON_AddStringToObject(root, "action", "index.html");
	cJSON_AddStringToObject(root, "method", "post");

	cJSON* html = cJSON_CreateArray();	
	cJSON_AddItemToArray(html, jsonDoubleField("kinectMotorAngle",0,-16,16,5) );
	cJSON_AddItemToArray(html, jsonIntField("minDepth",0,0,255,100) );
	cJSON_AddItemToArray(html, jsonIntField("maxDepth",0,255,255,100) );
	cJSON_AddItemToArray(html, jsonDoubleField("minBlobArea",256,16,4096*4,100) );
	cJSON_AddItemToArray(html, jsonDoubleField("maxBlobArea",2048,16,4096*8,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginLeft",0,0,KRES_X-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginRight",0,0,KRES_X-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginTop",0,0,KRES_Y-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginBottom",0,0,KRES_Y-1,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginFront",0,0,255,100) );
	cJSON_AddItemToArray(html, jsonIntField("marginBack",0,0,255,100) );
	cJSON_AddItemToArray(html, jsonCheckbox("TUIO_2Dcur",false) );
	cJSON_AddItemToArray(html, jsonCheckbox("TUIO_25Dblb",true) );
	cJSON_AddItemToArray(html, jsonCheckbox("areaThresh",true) );
	cJSON_AddItemToArray(html, jsonCheckbox("directFiltering",true) );
	cJSON_AddItemToArray(html, jsonCheckbox("clipping",true) );
/*
	cJSON* pareas = cJSON_CreateArray();
	cJSON* parea1 = cJSON_CreateObject();
	cJSON_AddNumberToObject(parea1, "top", 0 );
	cJSON_AddNumberToObject(parea1, "left", 0 );
	cJSON_AddNumberToObject(parea1, "width", 640 );
	cJSON_AddNumberToObject(parea1, "height", 480 );
	cJSON_AddItemToObject(pareas, "area1", parea1 );
	cJSON_AddItemToObject(root, "areas", pareas );
*/
	cJSON_AddItemToObject(root, "html", html);

	/* Point information for repoke */
	cJSON* areas = cJSON_CreateArray();	
	cJSON_AddItemToArray(areas, jsonArea(1,320.0,240.0,100.0) );
	cJSON_AddItemToObject(root, "areas", areas);
	return root;
}

int SettingKinect::update(cJSON* jsonNew, cJSON* jsonOld, int changes=NO){
	//parse_and_callback(m_pjson_root,"");//error
	cJSON* nhtml = cJSON_GetObjectItem(jsonNew,"html");
	cJSON* ohtml = jsonOld==NULL?NULL:cJSON_GetObjectItem(jsonOld,"html");
	if( nhtml != NULL){
		if( update(nhtml,ohtml,"kinectMotorAngle",&m_kinectMotorAngle) ) changes|=MOTOR;
		if( update(nhtml,ohtml,"minDepth",&m_minDepth) ) changes|=MARGIN|FRONT_MASK;
		if( update(nhtml,ohtml,"maxDepth",&m_maxDepth) ){
			changes|=MARGIN|FRONT_MASK;
			m_maxDepth = max(m_minDepth+2,m_maxDepth);
		}
		update(nhtml,ohtml,"minBlobArea",&m_minBlobArea);
		update(nhtml,ohtml,"maxBlobArea",&m_maxBlobArea);
		if( update(nhtml,ohtml,"marginLeft",&m_marginLeft) ) changes|=MARGIN;
		if( update(nhtml,ohtml,"marginRight",&m_marginRight) ) changes|=MARGIN;
		if( update(nhtml,ohtml,"marginTop",&m_marginTop) ) changes|=MARGIN;
		if( update(nhtml,ohtml,"marginBottom",&m_marginBottom) ) changes|=MARGIN;
		if( update(nhtml,ohtml,"marginFront",&m_marginFront) ) changes|=MARGIN|FRONT_MASK;
		if( update(nhtml,ohtml,"marginBack",&m_marginBack) ) changes|=BACK_MASK;

		if( updateCheckbox(nhtml,ohtml,"TUIO_2Dcur",&m_tuioProtocols[0]) ) changes|=TUIO_PROTOCOL;
		if( updateCheckbox(nhtml,ohtml,"TUIO_25Dblb",&m_tuioProtocols[1]) ) changes|=TUIO_PROTOCOL;
		if( updateCheckbox(nhtml,ohtml,"areaThresh",&m_areaThresh) ) changes|=BACK_MASK ; 
		if( updateCheckbox(nhtml,ohtml,"directFiltering",&m_directFiltering) ) changes|=BACK_MASK; 
		if( updateCheckbox(nhtml,ohtml,"clipping",&m_clipping) ){
			changes|=CLIPPING; 
		}
		//update region of interest
		int w,h,x,y;
		x = max(m_marginLeft,0);
		y = max(m_marginTop,0);
		w = max(KRES_X-m_marginLeft-m_marginRight,0);
		h = max(KRES_Y-m_marginTop-m_marginBottom,0);
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
				/*hm, to early. Need depth detection first */
				//changes|=REPOKE;//let imageanalysis search areas
			}
		}

		//call signal
		printf("Changes: %i\n",changes);
	  updateSig(this,changes);
	}
	return changes!=NO>0?1:0;
}

bool SettingKinect::update(cJSON* jsonNew, cJSON* jsonOld,const char* id, int* val){
	double tmp = *val;
	bool ret;
	ret = update(jsonNew, jsonOld, id, &tmp);
	*val = (int)tmp;
	return ret;
}

bool SettingKinect::update(cJSON* jsonNew, cJSON* jsonOld,const char* id, double* val){
	cJSON* ntmp = getArrayEntry(jsonNew,id);
	cJSON* otmp;
	bool ret(false);
	printf("update of %s:",id);				
	double nval=0.0, oval=*val;
	if( jsonOld != NULL && NULL != (otmp=getArrayEntry(jsonOld,id)) ){
		oval = getNumber(otmp,"val");//probably redundant.
		nval = doubleFieldValue(ntmp,otmp);
		if(oval!=nval) ret=true;
	}else if( ntmp != NULL){
		nval = doubleFieldValue(ntmp,ntmp);
		ret = true;
	}
	printf(" %f\n",nval);				
	/* If input data was manipulated on client side, nval can differ from "ntmp.val"
	 * nval conside [min_old,max_old] and "ntmp.val" not.
	 * An Update of ntmp.val is possible but avoided for performance reasons.
	 */
	*val = nval;
	return ret;
}

bool SettingKinect::updateCheckbox(cJSON* jsonNew, cJSON* jsonOld,const char* id, bool* val){
	cJSON* ntmp = getArrayEntry(jsonNew,id);
	cJSON* otmp;
	bool ret(false);
	printf("update of %s:",id);				
	double nval=0.0, oval=*val;
	if( jsonOld != NULL && NULL != (otmp=getArrayEntry(jsonOld,id)) ){
		oval = getNumber(otmp,"val");
		nval = getNumber(ntmp,"val");
		if(oval!=nval) ret=true;
	}else if( ntmp != NULL){
		nval = getNumber(ntmp,"val");
		ret = true;
	}
	printf(" %f\n",nval);				
	*val = nval==1;
	return ret;
}
bool SettingKinect::updateRoi(int x, int y, int width, int height){
	if( x<0 || y<0 || x+width>KRES_X || y+height>KRES_Y){
		return false;
	}
	m_roi.x = x;
	m_roi.y = y;
	m_roi.width = width;
	m_roi.height = height;
	//printf("Roi: (%i,%i,%i,%i)\n",m_roi.x,m_roi.y,m_roi.width,m_roi.height);
}

/*void SettingKinect::setDevice(MyFreenectDevice* device){
			m_device = device;
		};
*/
		
void SettingKinect::setAreas(std::vector<Area> &new_areas){

	//m_areas.clear();//redundant
	m_areas = new_areas;//copy vector 

	//update area field in settingKinect
	//cJSON* oareas = cJSON_GetObjectItem(m_pjson_root,"areas");  
	cJSON* areas = cJSON_CreateArray();	

	for(int i=0; i<m_areas.size(); i++){
		cJSON_AddItemToArray(areas, jsonArea(m_areas[i].id,m_areas[i].repoke_x,m_areas[i].repoke_y,m_areas[i].depth) );
	}

	m_pjson_mutex.lock();
	cJSON_ReplaceItemInObject(m_pjson_root, "areas", areas);
	m_pjson_mutex.unlock();
	//cJSON_Delete( );
	//printf("Json updated?!\n%s", getConfig());
}
