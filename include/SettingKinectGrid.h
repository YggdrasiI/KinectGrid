#ifndef SETTINGKINECTGRID_H
#define SETTINGKINECTGRID_H

#include "JsonConfig.h"


class SettingKinectGrid: public JsonConfig{
	private:
		FunctionMode m_mode;
	public:
		const char* m_host;
		const char* m_port;
		FunctionMode getModeAndLock();
		void setMode(FunctionMode mode);
		void unlockMode(FunctionMode mode);
	public:
		SettingKinectGrid() : m_mode(HAND_DETECTION),	JsonConfig()
		{
		};

	
		cJSON* loadDefaults();
		int update(cJSON* root, cJSON* update, int changes);

	protected:
		::Mutex m_mode_mutex;

};



#endif
