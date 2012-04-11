#include <stdlib.h>
#include <stdio.h>
#include "JsonConfig.h"

JsonConfig::JsonConfig()
{
	m_pjson_root = loadMinimal();
}

JsonConfig::JsonConfig(const char* filename)
{
	loadConfigFile(filename, loadMinimal);
}

JsonConfig::~JsonConfig()
{
	clearConfig();
}

int JsonConfig::clearConfig()
{
	if( m_pjson_root != NULL)
		cJSON_Delete(m_pjson_root);
}

int JsonConfig::setConfig(const char* json_str)
{
	clearConfig();
	m_pjson_root = cJSON_Parse(json_str);
	return 0;
}

char* JsonConfig::getConfig()const
{
	return cJSON_Print(m_pjson_root);
}

int JsonConfig::loadConfigFile(const char* filename, LoadDefaultsType* loadDefaultsFunc=NULL )
{
		clearConfig();
	if( FILE *f=fopen(filename,"rb") ){
		fseek(f,0,SEEK_END);
		long len=ftell(f);
		fseek(f,0,SEEK_SET);
		char *data=(char*)malloc(len+1);
		fread(data,1,len,f);
		fclose(f);

		setConfig(data);
		free(data);
	}else if(loadDefaultsFunc != NULL){
		printf("File not found. Use default values.\n");
		m_pjson_root = loadDefaultsFunc();
	}else{
		fprintf(stderr,"File not found.\n");
		return -1;
	}
	return 0;
}

int JsonConfig::saveConfigFile(const char* filename)
{
	FILE *file;
	file = fopen(filename,"w");
	fprintf(file,"%s", getConfig() );
	fclose(file); 
	return 0;
}

cJSON* JsonConfig::loadMinimal()
{
	cJSON* root = cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("unknown"));
	return root;
}

/*
 * General properties. Should only be called on first run to create settings.json file.
 */
cJSON* JsonConfig::loadMMTTlinuxSetting()
{
	cJSON* root = cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "type", cJSON_CreateString("settingMMTT"));
	cJSON_AddItemToObject(root, "host", cJSON_CreateString("0.0.0.0"));
	cJSON_AddItemToObject(root, "port", cJSON_CreateString("8080"));
	cJSON_AddItemToObject(root, "lastSetting", cJSON_CreateString("settingKinectDefault.json"));
	return root;
}

/*
 * Special properties. This values can modified with the web interface.
 * I.e. angle of kinect, nmbr of areas, position of areas, minimal blob size.
 */
cJSON* JsonConfig::loadKinectSetting()
{
	cJSON* root = cJSON_CreateObject();	
	cJSON* pareas = cJSON_CreateArray();
	cJSON* parea1 = cJSON_CreateObject();
	cJSON_AddStringToObject(root, "type", "settingKinect");
	cJSON_AddNumberToObject(root, "minBlobArea", 256 );

	cJSON_AddItemToObject(root, "areas", pareas );
	cJSON_AddItemToObject(pareas, "area1", parea1 );
	cJSON_AddNumberToObject(parea1, "top", 0 );
	cJSON_AddNumberToObject(parea1, "left", 0 );
	cJSON_AddNumberToObject(parea1, "width", 640 );
	cJSON_AddNumberToObject(parea1, "height", 480 );

	return root;
}
