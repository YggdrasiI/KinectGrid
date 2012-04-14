/*
 * Class provides the Loading and Saving of json files.
 * If the json contains some keywords postprocessing extract
 * and convert the content in a struct. 
 */
#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "cJSON.h"
#include "Mutex.h"
#include "constants.h"

/*
 * Functioal for second parameter of loadConfigFile method.
 * Use a function of this type to create default values if file is not found.
 */
typedef cJSON* LoadDefaultsType(void);

class JsonConfig{
	protected:
		cJSON* m_pjson_root;
		Mutex m_pjson_mutex;
	public:
		JsonConfig(LoadDefaultsType loadHandle=&JsonConfig::loadDefaults ):
			m_pjson_root(NULL)
		{
			m_pjson_root = loadHandle();
		};
		JsonConfig(const char* filename, LoadDefaultsType* loadHandle):
			m_pjson_root(NULL)
		{
			loadConfigFile(filename, loadHandle);
		};

		~JsonConfig(){
			clearConfig();
		};
	
		int setConfig(const char* json_str);
		char* getConfig();//const;
		int loadConfigFile(const char* filename, LoadDefaultsType* loadHandle=&JsonConfig::loadDefaults);
		int saveConfigFile(const char* filename);	
		/* create minimal json element
		 * This method can not be defined as virtual since it's called in constructors.
		 * */
		static cJSON* loadDefaults(){
			cJSON* root = cJSON_CreateObject();	
			cJSON_AddItemToObject(root, "kind", cJSON_CreateString("unknown"));
			printf("Should not execute.\n");
			return root;
		};
		cJSON* getJSON() {return m_pjson_root;};
	private:
		int clearConfig();
		virtual int update(cJSON* new_json, cJSON* old_json){	return 0; };
	public:
		/* Access to string child nodes of root node.*/
		const char* getString(const char* string)const{
			return getString(m_pjson_root, string);
		}
		static const char* getString(cJSON* r, const char* string){
			cJSON* obj = 	cJSON_GetObjectItem(r,string);
			if( obj != NULL && obj->type == cJSON_String)
				return obj->valuestring;
			else{
				printf("JsonConfig: Object %s not found.\n",string);
				static const char* notfound = "not found";
				return notfound;
			}
		}; 
		static double getNumber(cJSON* r, const char* string){
			cJSON* obj = 	cJSON_GetObjectItem(r,string);
			if( obj != NULL && obj->type == cJSON_Number)
				return obj->valuedouble;
			else{
				printf("JsonConfig: Object %s not found.\n",string);
				return -1;
			}
		};

		cJSON* getArrayEntry(cJSON* arr, const char* string)const{
			for(int i=0,n=cJSON_GetArraySize(arr);i<n;i++){
				cJSON* tmp = 	cJSON_GetArrayItem(arr,i);
				cJSON* id = 	cJSON_GetObjectItem(tmp,"id");
				if(id!=NULL && !strcmp(id->valuestring,string)) return tmp;
			}
			return NULL;
		};

		/* Do not trust range limitation of http request.
		 * Instead, use range limitation of old config.
		 */
		static double doubleFieldValue(cJSON* ndf, cJSON* odf){
			return min(max(getNumber(odf,"min"),getNumber(ndf,"val")),getNumber(odf,"max"));
		}
		inline int intFieldValue(cJSON* ndf, cJSON* odf){return (int)doubleFieldValue(ndf,odf); }

};

/*
 * json representation of extended html input field.
 */
static cJSON* jsonDoubleField(const char* id, double val, double min, double max, double diff){
	cJSON* df = cJSON_CreateObject();
	cJSON_AddStringToObject(df, "type", "doubleField");
	cJSON_AddStringToObject(df, "id", id);
	cJSON_AddNumberToObject(df, "val", val );
	cJSON_AddNumberToObject(df, "min", min );
	cJSON_AddNumberToObject(df, "max", max );
	cJSON_AddNumberToObject(df, "diff", diff );

	return df;
}
static cJSON* jsonIntField(const char* id, int val, int min, int max, int diff){
	cJSON* df = cJSON_CreateObject();
	cJSON_AddStringToObject(df, "type", "intField");
	cJSON_AddStringToObject(df, "id", id);
	cJSON_AddNumberToObject(df, "val", val );
	cJSON_AddNumberToObject(df, "min", min );
	cJSON_AddNumberToObject(df, "max", max );
	cJSON_AddNumberToObject(df, "diff", diff );

	return df;
}

#endif
