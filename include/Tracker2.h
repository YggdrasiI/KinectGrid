/*
 * Tracker for myblob lib.
 */

#ifndef TRACKER2_H
#define TRACKER2_H

#include "Tracker.h"
#include "myblob.h" //myblob lib header


class Tracker2: public Tracker {
	private:
		Myblob *m_blob;

	public:
		Tracker2(SettingKinect* pSettingKinect);
		Tracker2(double min_area, double max_area, double max_radius);
		~Tracker2();

		void trackBlobs(
				const Mat &mat, const Mat &areaMask,
				bool history,
				std::vector<Area> *pareas ) ;
};


#endif
