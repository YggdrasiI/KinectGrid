/*
 * Tracker which use own/fast blob detection lib.
 */

#ifndef TRACKER2_H
#define TRACKER2_H

#include "Tracker.h"
#include "threshtree.h" 


class Tracker2: public Tracker {
	private:
		Blobtree *m_blob;
		ThreshtreeWorkspace *m_workspace;

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
