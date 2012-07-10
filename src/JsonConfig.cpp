#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "JsonConfig.h"

int JsonConfig::clearConfig()
{
	m_pjson_mutex.lock();
	if( m_pjson_root != NULL){
		cJSON_Delete(m_pjson_root);
		m_pjson_root = NULL;
	}
	m_pjson_mutex.unlock();
}

int JsonConfig::setConfig(const char* json_str, int changes=NO)
{
	cJSON* pNewRoot = cJSON_Parse(json_str);
	if( pNewRoot == NULL ) return -1;
	/* Not call setConfig from construtor. update is virtual. Use init() instead.*/
	update(pNewRoot,m_pjson_root, changes);

	clearConfig();
	m_pjson_mutex.lock();
	m_pjson_root = pNewRoot;
	m_pjson_mutex.unlock();
	return 0;
}

char* JsonConfig::getConfig()//const
{
	return cJSON_Print(m_pjson_root);
}

int JsonConfig::loadConfigFile(const char* filename)
{
		clearConfig();
	if( FILE *f=fopen(filename,"rb") ){
		fseek(f,0,SEEK_END);
		long len=ftell(f);
		fseek(f,0,SEEK_SET);
		char *data=(char*)malloc(len+1);
		fread(data,1,len,f);
		fclose(f);

		setConfig(data, CONFIG);
		free(data);
	}else{
		printf("File %s not found. Use default values.\n",filename);
		m_pjson_root = loadDefaults();
		return 1;
	}
	return 0;
}

int JsonConfig::saveConfigFile(const char* filename)
{
	FILE *file;
	file = fopen(filename,"w");
	char* conf = getConfig();
	fprintf(file,"%s", conf );
	free(conf);
	fclose(file); 
	return 0;
}

cJSON* JsonConfig::loadDefaults()
{
cJSON* root = cJSON_CreateObject();	
cJSON_AddItemToObject(root, "kind", cJSON_CreateString("unknown"));
printf("Should not execute.\n");
return root;
}


int JsonConfig::update(cJSON* new_json, cJSON* old_json, int changes=NO)
{
	printf("Error (JsonConfig): Parent update method called.\n");
	return 0;
};

