/* Abstract Tracker class. 
 * Implementations: TrackerCvBlobsLib, Tracker2.
 */

#ifndef TRACKER_H
#define TRACKER_H

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>

#include "blob.h"
#include "SettingKinect.h"

using namespace cv;

class Tracker {
	protected:

		/* m_p*_area points to m_min_area if constructor without SettingKinect was used.
		 * Otherwise to m_pSettingKinect->m_*BlobArea.
		 */
		double *m_pmin_area, *m_pmax_area, *m_pmax_radius;
		double m_min_area, m_max_area, m_max_radius;
		bool *m_pnotDrawBlob;
		bool m_notDrawBlob;
		SettingKinect* m_pSettingKinect;

		std::vector<cBlob> blobs, blobs_previous;

		// storage of used handids
		bool handids[MAXHANDS];
		int last_handid;

	public:
		Tracker(SettingKinect* pSettingKinect);
		Tracker(double min_area, double max_area, double max_radius);
		virtual ~Tracker() = 0;
		std::vector<cBlob>& getBlobs();

		virtual void trackBlobs(
				const Mat &mat, const Mat &areaMask,
				bool history,
				std::vector<Area> *pareas ) = 0;

};


#endif
