#ifndef TRACKER_H
#define TRACKER_H

#include <opencv/cv.h>
#include "../cvblobslib/BlobResult.h"
#include <vector>
#include "blob.h"

class Tracker {
  private:
	CBlobResult blob_result;
	CBlob *current_blob;
	
	double min_area, max_radius;

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
	Tracker(double min_area, double max_radius);
	~Tracker();
	
	void trackBlobs(cv::Mat &mat, bool history);
	std::vector<cBlob>& getBlobs();
};


#endif
