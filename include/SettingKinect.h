#ifndef SETTINGKINECT_H
#define SETTINGKINECT_H

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <queue>

#include <onion/onion.hpp>
#include <onion/response.hpp>
#include <onion/request.hpp>

#include <boost/signal.hpp>
#include <boost/regex.hpp> 
//#include <boost/bind.hpp>

#include "JsonConfig.h"
#include "JsonMessage.h"

//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>

/* Wrapper struct for some properties. */
struct KinectProperties{
	double kinectMotorAngle;
	int maxDepth;
	int minDepth;
	double minBlobArea;
	double maxBlobArea;
	int marginLeft;
	int marginRight;
	int marginTop;
	int marginBottom;
	int marginFront;
	int marginBack;
	bool areaThresh;
	bool directFiltering;
	bool clipping;
	cv::Rect roi;
	std::vector<Area> areas;
};


class SettingKinect: public JsonConfig{
	private:
		FunctionMode m_mode;
	protected:
		::Mutex m_mode_mutex;
	public:
		std::string m_host;
		std::string m_port;
		bool m_tuioProtocols[2];
		std::string m_tuio2Dcur_host;
		std::string m_tuio25Dblb_host;
		int m_tuio2Dcur_port;
		int m_tuio25Dblb_port;
		std::vector<Area> m_areas;

		KinectProperties m_kinectProp;

		boost::signal<void (SettingKinect* pSettingKinect, int)> updateSig; //alt?!

		/* Update signal. Will send at the end of update(...) */
		boost::signal<void (int changes)> updateSettings;

		/* This object owns his own mutexes.
			This could cause deadlocks if some mutexes will enwinded... 
			*/
		Messages m_queues; 
		std::string m_configFilename;

		/* Map [0,....,2047] to [0,....,0,1,....,254,255,....,255,0]
		 * require (and get) update on changes of m_maxDepth or m_minDepth
		 */
		uint8_t /*unsigned char*/ m_rangeMap[2048];

	public:
		FunctionMode getModeAndLock();
		void setMode(FunctionMode mode);
		void unlockMode(FunctionMode mode);


	private:
		//similar to updateIntField in JsonConfig.
		bool updateState(cJSON* jsonNew, cJSON* jsonOld,const char* id, int* val);
		bool updateState(cJSON* jsonNew, cJSON* jsonOld,const char* id, double* val);

		bool update(cJSON* jsonNew, cJSON* jsonOld,const char* id, int* val);//alt?!
		bool update(cJSON* jsonNew, cJSON* jsonOld,const char* id, double* val);//alt?!
		bool updateCheckbox(cJSON* jsonNew, cJSON* jsonOld,const char* id, bool* val);

	public:
		SettingKinect();
		~SettingKinect();

		void loadDefaults();
		cJSON* genJson();
		int update(cJSON* jsonNew, cJSON* jsonOld, int changes=NO);//override virtual method

		/* Will called if website send data */
		bool webserverUpdateConfig(Onion::Request *preq, int actionid, Onion::Response *pres);

		/* Overwrite two methodes to save filename */
		int loadConfigFile(const char* filename){
			m_configFilename = filename;	
			return JsonConfig::loadConfigFile(filename);
		};
		int init(const char* filename="")
		{
			m_configFilename = filename;
			return JsonConfig::init(filename);
		};

		/* Get json struct of current open files. */
		cJSON *jsonFilesField(const char* id);

		bool updateRoi(int x, int y, int width, int height);
		void setAreas(std::vector<Area> &new_areas);

};



#endif
