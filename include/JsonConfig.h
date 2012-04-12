/*
 * Class provides the Loading and Saving of json files.
 * If the json contains some keywords postprocessing extract
 * and convert the content in a struct. 
 */
#ifndef JSONCONFIG_H
#define JSONCONFIG_H

#include "cJSON.h"
#include "settingStructs.h"

/*
 * Functioal for second parameter of loadConfigFile method.
 * Use a function of this type to create default values if file is not found.
 */
typedef cJSON* LoadDefaultsType(void);

class JsonConfig{
	private:
		cJSON* m_pjson_root;
	public:
		JsonConfig();
		JsonConfig(const char* filename, LoadDefaultsType* loadDefaultsFunc=NULL);
		~JsonConfig();
	
		int setConfig(const char* json_str);
		char* getConfig()const;
		cJSON* getJSON() {return m_pjson_root;};
		int loadConfigFile(const char* filename, LoadDefaultsType* loadDefaultsFunc);
		int saveConfigFile(const char* filename);	
		/* create minimal json element */
		int loadDefaults();
		static cJSON* loadMinimal();
		static cJSON* loadMMTTlinuxSetting();
		static cJSON* loadKinectSetting();
	private:
		int clearConfig();
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

#endif
