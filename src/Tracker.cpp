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
