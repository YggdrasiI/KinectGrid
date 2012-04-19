/*
 * Code from: 
 * http://www.keithlantz.net/2011/04/detecting-blobs-with-cvblobslib-and-tracking-blob-events-across-frames/
 */

#ifndef TRACKER_H
#define TRACKER_H

#include <opencv/cv.h>
#include "../cvblobslib/BlobResult.h"
#include <vector>
#include "blob.h"

#include "SettingKinect.h"

class Tracker {
  private:
	CBlobResult blob_result;
	CBlob *current_blob;

	/* m_p*_area points to m_min_area if constructor without SettingKinect was used.
	 * Otherwise to m_pSettingKinect->m_*BlobArea.
	 */
	double *m_pmin_area, *m_pmax_area, *m_pmax_radius;
	double m_min_area, m_max_area, m_max_radius;
	SettingKinect* m_pSettingKinect;

	// instances of helper classes for obtaining blob location and bounding box
	CBlobGetXCenter XCenter;
	CBlobGetYCenter YCenter;
	CBlobGetMinX MinX;
	CBlobGetMinY MinY;
	CBlobGetMaxX MaxX;
	CBlobGetMaxY MaxY;

	// we will convert the matrix object passed from our cFilter class to an object of type IplImage for calling the CBlobResult constructor
	IplImage img;

	// storage of the current blobs and the blobs from the previous frame
	std::vector<cBlob> blobs, blobs_previous;

  protected:

  public:
	Tracker(SettingKinect* pSettingKinect);
	Tracker(double min_area, double max_area, double max_radius);
	~Tracker();
	
	void trackBlobs(cv::Mat &mat, bool history);
	std::vector<cBlob>& getBlobs();
};


#endif
