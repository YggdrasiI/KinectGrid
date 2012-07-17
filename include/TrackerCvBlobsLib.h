/*
 * Code from: 
 * http://www.keithlantz.net/2011/04/detecting-blobs-with-cvblobslib-and-tracking-blob-events-across-frames/
 */

#ifndef TRACKER_CVBLOBSLIB_H
#define TRACKER_CVBLOBSLIB_H

#include "Tracker.h"
#include "../cvblobslib/BlobResult.h"


class TrackerCvBlobsLib: public Tracker{
	private:
		CBlobResult blob_result;
		CBlob *current_blob;

		// instances of helper classes for obtaining blob location and bounding box
		CBlobGetXCenter XCenter;
		CBlobGetYCenter YCenter;
		CBlobGetMinX MinX;
		CBlobGetMinY MinY;
		CBlobGetMaxX MaxX;
		CBlobGetMaxY MaxY;

	public:
		TrackerCvBlobsLib(SettingKinect* pSettingKinect);
		TrackerCvBlobsLib(double min_area, double max_area, double max_radius);
		~TrackerCvBlobsLib();
		
		void trackBlobs(
				const Mat &mat, const Mat &areaMask,
				bool history,
				std::vector<Area> *pareas );

};


#endif
