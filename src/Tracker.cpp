/*
 * Code from: 
 * http://www.keithlantz.net/2011/04/detecting-blobs-with-cvblobslib-and-tracking-blob-events-across-frames/
 */

#include "Tracker.h"

Tracker::Tracker(double min_area, double max_area, double max_radius) : m_pSettingKinect(NULL), m_min_area(min_area), m_max_area(max_area), m_max_radius(max_radius)
{
	m_pmin_area = &m_min_area;
	m_pmax_area = &m_max_area;
	m_pmax_radius = &m_max_radius;
}

Tracker::Tracker(SettingKinect* pSettingKinect) : m_pSettingKinect(pSettingKinect), m_min_area(-1.0/*pSettingKinect->m_minBlobArea*/), m_max_area(-1.0/*pSettingKinect->m_maxBlobArea*/), m_max_radius(TMAXRADIUS)
{
	m_pmin_area = &(m_pSettingKinect->m_minBlobArea);
	m_pmax_area = &(m_pSettingKinect->m_maxBlobArea);
	m_pmax_radius = &m_max_radius;
}

Tracker::~Tracker()
{
}

void Tracker::trackBlobs(cv::Mat &mat, bool history)
{
	double min_area = *m_pmin_area;
	double max_area = *m_pmax_area;
	double max_radius = *m_pmax_radius;
	double x, y, min_x, min_y, max_x, max_y;
	cBlob temp;

	// convert our OpenCV matrix object to one of type IplImage
	img = mat;

	// cvblobslib blob extraction
	blob_result = CBlobResult(&img, NULL, 127/*img∈{0,255}->thresh unimportant*/, false);
	blob_result.Filter(blob_result, B_EXCLUDE, CBlobGetArea(), B_LESS, min_area); 
	blob_result.Filter(blob_result, B_EXCLUDE, CBlobGetArea(), B_GREATER, max_area);

	// clear the blobs from two frames ago
	blobs_previous.clear();
	
	// before we populate the blobs vector with the current frame, we need to store the live blobs in blobs_previous
	for (int i = 0; i < blobs.size(); i++)
		if (blobs[i].event != BLOB_UP)
			blobs_previous.push_back(blobs[i]);


	// populate the blobs vector with the current frame
	blobs.clear();
	for (int i = 1; i < blob_result.GetNumBlobs(); i++) {
		current_blob = blob_result.GetBlob(i);

		x     = XCenter(current_blob);
		y     = YCenter(current_blob);
		min_x = MinX(current_blob);
		min_y = MinY(current_blob);
		max_x = MaxX(current_blob);
		max_y = MaxY(current_blob);

		temp.location.x = temp.origin.x = x;
		temp.location.y = temp.origin.y = y;
		temp.min.x = min_x; temp.min.y = min_y;
		temp.max.x = max_x; temp.max.y = max_y;
		temp.event = BLOB_DOWN;

		blobs.push_back(temp);
	}

	// initialize previous blobs to untracked
	for (int i = 0; i < blobs_previous.size(); i++) blobs_previous[i].tracked = false;

	// main tracking loop -- O(n^2) -- simply looks for a blob in the previous frame within a specified radius
	for (int i = 0; i < blobs.size(); i++) {
		for (int j = 0; j < blobs_previous.size(); j++) {
			if (blobs_previous[j].tracked) continue;

			if (sqrt(pow(blobs[i].location.x - blobs_previous[j].location.x, 2.0) + pow(blobs[i].location.y - blobs_previous[j].location.y, 2.0)) < max_radius) {
				blobs_previous[j].tracked = true;
				blobs[i].event = BLOB_MOVE;
				blobs[i].origin.x = history ? blobs_previous[j].origin.x : blobs_previous[j].location.x;
				blobs[i].origin.y = history ? blobs_previous[j].origin.y : blobs_previous[j].location.y;
			}
		}
	}

	// add any blobs from the previous frame that weren't tracked as having been removed
	for (int i = 0; i < blobs_previous.size(); i++) {
		if (!blobs_previous[i].tracked) {
			blobs_previous[i].event = BLOB_UP;
			blobs.push_back(blobs_previous[i]);
		}
	}

	for (int i = 1; i < blob_result.GetNumBlobs(); i++) {
				current_blob = blob_result.GetBlob(i);
				printf("Blobcoordsd %f, %f\n", XCenter(current_blob), YCenter(current_blob) );
	}

}

std::vector<cBlob>& Tracker::getBlobs()
{
	return blobs;
}
