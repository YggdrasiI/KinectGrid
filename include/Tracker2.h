/*
 * Tracker for myblob lib.
 */

#ifndef TRACKER2_H
#define TRACKER2_H

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <vector>

#include "SettingKinect.h"
#include "blob.h" // header of this project
#include "myblob.h" //myblob lib header


class Tracker2 {
  private:
	Myblob *m_blob;

	/* m_p*_area points to m_min_area if constructor without SettingKinect was used.
	 * Otherwise to m_pSettingKinect->m_*BlobArea.
	 */
	double *m_pmin_area, *m_pmax_area, *m_pmax_radius;
	double m_min_area, m_max_area, m_max_radius;
	bool *m_pnotDrawBlob;
	bool m_notDrawBlob;
	SettingKinect* m_pSettingKinect;

	// we will convert the matrix object passed from our cFilter class to an object of type IplImage for calling the CBlobResult constructor
	IplImage img;
	IplImage areaImg;

	// storage of the current blobs and the blobs from the previous frame
	std::vector<cBlob> blobs, blobs_previous;

	// storage of used handids
	bool handids[MAXHANDS];
	int last_handid;

  protected:

  public:
	Tracker2(SettingKinect* pSettingKinect);
	Tracker2(double min_area, double max_area, double max_radius);
	~Tracker2();
	
	void trackBlobs(const Mat &mat, const Mat &areaMask, bool history, std::vector<Area> *pareas);
	std::vector<cBlob>& getBlobs();
};


#endif
