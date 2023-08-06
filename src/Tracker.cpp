/* Abstract Tracker class. 
 * Implementations: TrackerCvBlobsLib, Tracker2.
 */

#include "Tracker.h"

Tracker::Tracker(double min_area, double max_area, double max_radius) : m_pSettingKinect(NULL), m_min_area(min_area), m_max_area(max_area), m_max_radius(max_radius),
	m_notDrawBlob(false)
#ifdef CENTER_ADJUSTMENT
											, m_count_N(20U)
#endif
{
	m_pmin_area = &m_min_area;
	m_pmax_area = &m_max_area;
	m_pmax_radius = &m_max_radius;
	m_pnotDrawBlob = &m_notDrawBlob;

	for(int i=0; i<MAXHANDS; i++) handids[i] = false;
	last_handid = 0;

}

Tracker::Tracker(SettingKinect* pSettingKinect) : m_pSettingKinect(pSettingKinect), m_min_area(-1.0), m_max_area(-1.0),
	m_max_radius(TMAXRADIUS)
#ifdef CENTER_ADJUSTMENT
													, m_count_N(20U)
#endif
{
	m_pmin_area = &(m_pSettingKinect->m_kinectProp.minBlobArea);
	m_pmax_area = &(m_pSettingKinect->m_kinectProp.maxBlobArea);
	m_pmax_radius = &m_max_radius;
	m_pnotDrawBlob = &(m_pSettingKinect->m_kinectProp.directFiltering);/*Avoid drawing of Blob limits. */

	for(int i=0; i<MAXHANDS; i++) handids[i] = false;
	last_handid = 0;
}

Tracker::~Tracker(){}

std::vector<cBlob>& Tracker::getBlobs()
{
	return blobs;
}

#ifdef CENTER_ADJUSTMENT
template<typename T> void Tracker::get_tip(
		const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
		T *outx, T *outy, T *outz)
{

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

void Tracker::get_tip(const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
		int *outx, int *outy, int *outz)
{

	return get_tip<int>(roi, depth, thresh, outx, outy, outz);
}
void Tracker::get_tip(const cv::Rect roi, const cv::Mat &depth, const uint8_t thresh,
		double *outx, double *outy, double *outz)
{
	return get_tip<double>(roi, depth, thresh, outx, outy, outz);
}
#endif
