/* Abstract Tracker class. 
 * Implementations: TrackerCvBlobsLib, Tracker2.
 */

#ifndef TRACKER_H
#define TRACKER_H

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

#include "blob.h"
#include "SettingKinect.h"

//using namespace cv;

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

#ifdef CENTER_ADJUSTMENT
		/* Use (at least) m_count_N pixel with biggest depth to eval depth of blob tip. */
		const uint32_t m_count_N;
		uint32_t m_mean_x[256];
		uint32_t m_mean_y[256];
#endif

	public:
		Tracker(SettingKinect* pSettingKinect);
		Tracker(double min_area, double max_area, double max_radius);
		virtual ~Tracker() = 0;
		std::vector<cBlob>& getBlobs();

		virtual void trackBlobs(
				const cv::Mat &mat, const cv::Mat &areaMask,
				bool history,
				std::vector<Area> *pareas ) = 0;

#ifdef CENTER_ADJUSTMENT
	private:
		template<typename T> void get_tip(
				const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
				T *outx, T *outy, T *outz);
	public:
		void get_tip(const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
				int *outx, int *outy, int *outz);
		void get_tip(const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
				double *outx, double *outy, double *outz);
#endif


};


#ifdef CENTER_ADJUSTMENT
/* Assume weightMap array has 512 elements.
 * Params depth, mask should already shrinked to roi.
 * Mask argument comment out because this mask was already applied.
 * */
static void get_tip_pos(int z, cv::Rect roi, cv::Mat &depth,/* cv::Mat &mask,*/
		uint8_t *weightMap, float *outx, float *outy){

	uint8_t* pz = weightMap+256;
	uint32_t sumx = 0;
	uint32_t countx = 0;
	uint32_t sumy = 0;
	uint32_t county = 0;
	uint8_t w;
	cv::MatConstIterator_<uint8_t> itDepth = depth.begin<uint8_t>();
//	cv::MatConstIterator_<uint8_t> itMask = mask.begin<uint8_t>();
		
	//for( ; it1 != it1_end; ++it1, ++it2, ++dst_it ) 
	for( int x=0; x<roi.width; x++){
		for(int y=0; y<roi.height; y++){
//			if( *itMask ){
				w = pz[z-*itDepth];
				sumx += x*w;
				countx += w;
				sumy += y*w;
				county += w;
//			}
			++itDepth;
//			++itMask;
		}
	}

	*outx = sumx/countx + roi.x;
	*outy = sumy/county + roi.y;
}

#endif

#endif
