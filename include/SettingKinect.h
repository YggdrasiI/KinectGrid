#ifndef SETTINGKINECT_H
#define SETTINGKINECT_H

#include  <vector>
#include  <cv.h>
#include <boost/signal.hpp>
#include <boost/bind.hpp>

#include "JsonConfig.h"

using namespace cv;

//enum Mode {SHOW_BLOBS, SHOW_AREAS, DETECT_AREAS};
//enum Mode {MODE_FIND_BLOBS, MODE_SHOW_AREAS, MODE_DETECT_AREAS};

class SettingKinect: public JsonConfig{
	public:
		double m_kinectMotorAngle;
		int m_maxDepth;
		int m_minDepth;
		double m_minBlobArea;
		double m_maxBlobArea;
		int m_marginLeft;
		int m_marginRight;
		int m_marginTop;
		int m_marginBottom;
		int m_marginFront;
		int m_marginBack;
		bool m_tuioProtocols[2];
		bool m_areaThresh;
		bool m_directFiltering;
		bool m_clipping;
		Rect m_roi;
		std::vector<Area> m_areas;
//	  Sleep m_sleep;
//		Mode m_mode;
		boost::signal<void (SettingKinect* pSettingKinect, int)> updateSig;
	private:
	//	MyFreenectDevice* m_device;
	public:
		SettingKinect() : /*m_mode(SHOW_BLOBS),*/ m_roi(0,0,KRES_X,KRES_Y),m_minDepth(0),m_maxDepth(255), JsonConfig()//, m_sleep(false,SLEEPMODE_DURATION)
		{
		};

		cJSON* loadDefaults();
		int update(cJSON* jsonNew, cJSON* jsonOld, int changes);//override virtual method

		/* Map [0,....,2047] to [0,....,0,1,....,254,255,....,255]
		 * require (and get) update on changes of m_maxDepth or m_minDepth
		 */
		uint8_t /*unsigned char*/ m_rangeMap[2048];

	private:
		bool update(cJSON* jsonNew, cJSON* jsonOld,const char* id, int* val);
		bool update(cJSON* jsonNew, cJSON* jsonOld,const char* id, double* val);
		bool updateCheckbox(cJSON* jsonNew, cJSON* jsonOld,const char* id, bool* val);

	public:
		bool updateRoi(int x, int y, int width, int height);
		void setAreas(std::vector<Area> &new_areas);
	//	void setDevice(MyFreenectDevice* device);

};



#endif
