#include "SettingKinectGrid.h"

/*
 * Special properties. This values can modified with the web interface.
 * I.e. angle of kinect, nmbr of areas, position of areas, minimal blob size.
 */
cJSON* SettingKinectGrid::loadDefaults()
{
	cJSON* root = cJSON_CreateObject();	
	//cJSON_AddItemToObject(root, "type", cJSON_CreateString("settingKinectGrid"));//type is keyword in formular generation
	cJSON_AddItemToObject(root, "kind", cJSON_CreateString("settingKinectGrid"));
	cJSON_AddItemToObject(root, "host", cJSON_CreateString("0.0.0.0"));
	cJSON_AddItemToObject(root, "port", cJSON_CreateString("8080"));
	cJSON_AddItemToObject(root, "lastSetting", cJSON_CreateString("settingKinectDefault.json"));
	cJSON_AddItemToObject(root, "tuio2Dcur_host", cJSON_CreateString("127.0.0.01"));
	cJSON_AddItemToObject(root, "tuio2Dcur_port", cJSON_CreateNumber(3333));
	cJSON_AddItemToObject(root, "tuio25Dblb_host", cJSON_CreateString("127.0.0.01"));
	cJSON_AddItemToObject(root, "tuio25Dblb_port", cJSON_CreateNumber(3335));
	return root;
};

int SettingKinectGrid::update(cJSON* root, cJSON* update, int changes=NO){
	return 1;
};

/* Ignore value if an different value was set by other thread */
void SettingKinectGrid::setMode(FunctionMode mode){
	m_mode_mutex.lock();
	m_mode = mode;
	m_mode_mutex.unlock();
}
FunctionMode SettingKinectGrid::getModeAndLock(){
	m_mode_mutex.lock();
	return m_mode;
}

void SettingKinectGrid::unlockMode(FunctionMode mode){
	m_mode = mode;
	m_mode_mutex.unlock();
}
