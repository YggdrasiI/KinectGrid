/*
 * Tracker which use own/fast blob detection lib.
 */

#ifndef TRACKER2_H
#define TRACKER2_H

#include "Tracker.h"
namespace Blob { // Namespace avoids collision with OpenCv's Node
#include "blobdetection/threshtree.h" 
}


class Tracker2: public Tracker {
	private:
		Blob::Blobtree *m_blob;
		Blob::ThreshtreeWorkspace *m_workspace;

	public:
		Tracker2(SettingKinect* pSettingKinect);
		Tracker2(double min_area, double max_area, double max_radius);
		~Tracker2();

		void trackBlobs(
				const cv::Mat &mat, const cv::Mat &areaMask,
				bool history,
				std::vector<Area> *pareas ) ;
};


#endif
