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
		void get_tip(const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
				double *outx, double *outy, double *outz){

			const uint32_t &N = m_count_N;

			if( roi.width*roi.height<N){
				*outz = max(thresh,mean( depth, depth )[0]);
				*outx = roi.x + roi.width/2;
				*outy = roi.y + roi.width/2;
				return;
			}

			uint32_t *count = (uint32_t*) calloc(256,sizeof(uint32_t));
			uint8_t max=thresh;
			int N2 = 0;
			int sumX=0,sumY=0,sumZ=0;

			cv::MatConstIterator_<uint8_t> itDepth = depth.begin<uint8_t>();

			//Debug.. (unrequired) clearing
			for( int i=0; i<256; i++){ m_mean_x[i] = 0; m_mean_y[i] = 0; }

			//m_mean_x[thresh] = 0;
			//m_mean_y[thresh] = 0;
			uint32_t pixelsWithLowDepth = roi.height*roi.width;

			for(int y=0; y<roi.height; y++){
				for( int x=0; x<roi.width; x++){
					if(*itDepth>thresh){
						if( count[*itDepth] ){
							count[*itDepth]++;
							m_mean_x[*itDepth] += x;
							m_mean_y[*itDepth] += y;
						}else{
							if(*itDepth>max) max=*itDepth;
							count[*itDepth]++;
							m_mean_x[*itDepth] = x;
							m_mean_y[*itDepth] = y;
						}
						--pixelsWithLowDepth;
					}
					//cut down unimportant mean evaluation for the thresh level (see comment below.)
					/*else{ 
						count[thresh]++;
						m_mean_x[thresh] += x;
						m_mean_y[thresh] += y;
					}*/
					++itDepth;
				}
			}

			/* The used mean for pixels with depth <= thresh 
			 * will just approximated here. The exact value
			 * is not important because this values only
			 * affects the case with insufficient pixels 
			 * for a reliable tip detection.
			 */
			count[thresh] = pixelsWithLowDepth;
			m_mean_x[thresh] = pixelsWithLowDepth*roi.width/2;
			m_mean_y[thresh] = pixelsWithLowDepth*roi.height/2;

			//while( max>=thresh ){
			while( N2<N && max>=thresh ){
				if(count[max]){
					sumZ+=count[max]*max;
					sumX+=m_mean_x[max];
					sumY+=m_mean_y[max];
					N2+=count[max];
					//if( N2>=N ) break;
				}
				max--;
			}
			//if you want the weight of EXACT N elements subtract (N-N2)*ARRAY[max+1] here...

			*outx = ((double)sumX)/N2 + roi.x;
			*outy = ((double)sumY)/N2 + roi.y;
			*outz = ((double)sumZ)/N2;

			free(count);
		}
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
