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

	for(int i=0; i<MAXHANDS; i++) handids[i] = false;
	last_handid = 0;
}

Tracker::Tracker(SettingKinect* pSettingKinect) : m_pSettingKinect(pSettingKinect), m_min_area(-1.0/*pSettingKinect->m_minBlobArea*/), m_max_area(-1.0/*pSettingKinect->m_maxBlobArea*/), m_max_radius(TMAXRADIUS)
{
	m_pmin_area = &(m_pSettingKinect->m_minBlobArea);
	m_pmax_area = &(m_pSettingKinect->m_maxBlobArea);
	m_pmax_radius = &m_max_radius;

	for(int i=0; i<MAXHANDS; i++) handids[i] = false;
	last_handid = 0;
}

Tracker::~Tracker()
{
}

void Tracker::trackBlobs(const Mat &mat, const Mat &areaMask, bool history, std::vector<Area> *pareas)
{
	double min_area = *m_pmin_area;
	double max_area = *m_pmax_area;
	double max_radius = *m_pmax_radius;
	double x, y, min_x, min_y, max_x, max_y;
	double min_depth,max_depth;
	Scalar sdepth, sstddev;
	cBlob temp;
	bool new_hand(true);
	int mat_area(mat.size().width*mat.size().height);

	Size s;	Point p;
	mat.locateROI(s,p);
	areaImg = areaMask;

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
	for (int i = 0; i < blob_result.GetNumBlobs(); i++) {
		current_blob = blob_result.GetBlob(i);

		x     = XCenter(current_blob)/*+m_pSettingKinect->m_roi.x*/;
		y     = YCenter(current_blob)/*+m_pSettingkinect->m_roi.y*/;

//		temp.areaid = areaMask.at<uchar>((int)x+p.x,(int)y+p.y);//?!not works
		temp.areaid = (uchar) areaImg.imageData[ ((int)x+p.x) + ((int)y+p.y)*areaMask.size().width];//works
		if( temp.areaid == 0 ) continue;

		min_x = MinX(current_blob);
		min_y = MinY(current_blob);
		max_x = MaxX(current_blob);
		max_y = MaxY(current_blob);

		if( (max_x-min_x)*(max_y-min_y) > 0.9*mat_area) continue;// fix blob detection issue?!

		temp.location.x = temp.origin.x = x;
		temp.location.y = temp.origin.y = y;
		temp.min.x = min_x; temp.min.y = min_y;
		temp.max.x = max_x; temp.max.y = max_y;

		//Rect r(min_x+p.x,min_y+p.x, max_x-min_y, max_y-min_y);
		//Rect r(min_x,min_y, max_x-min_x, max_y-min_y);//width, height +1?!
		Rect r( x, y, 7, 7);


		//z = mean( mat(r), mat(r) )[0];/* mean is not good. The blob can include many pixel behind the frame depth*/

		/* Depth detection. The measurement method is flexible. */
		if( m_pSettingKinect->m_areaThresh ){
			/* Mean is ok, because all pixels of the blob are in front of the frame. */
			max_depth = mean( mat(r), mat(r) )[0]+4;/*correct blur(1) and area thresh shift (3)*/
			//meanStdDev( mat(r), sdepth, sstddev, mat(r) );
			//max_depth = sdepth[0]+3*sstddev[0];
			//minMaxLoc( mat(r), &min_depth, &max_depth, NULL, NULL, mat(r) );

		}else	if( pareas != NULL){
			/* Remove values behind the area depth and count mean of rest.
				This is problematic/choppy if to many pixels are removed.
			*/
			max_depth = max( (*pareas)[temp.areaid-1].depth-22, 
					mean( mat(r), mat(r)>(*pareas)[temp.areaid-1].depth-2 )[0] + 1);

		}else{
			/* Very few information. Use maximum of blob. (Choppy).
			 * Can be improved, if mean of i.e. 10 biggest values is used
			 * minMaxLoc require filtered/blured images.
			 * */
			//max_depth = 0;
			minMaxLoc( mat(r), &min_depth, &max_depth, NULL, NULL, mat(r) );
		}
		//printf("Compared depth of area/blob: %i %f\n",(*pareas)[temp.areaid-1].depth ,max_depth);

		/* Compare depth of hand with depth of area and throw blob away if hand to far away. */
		if(pareas != NULL && max_depth - (*pareas)[temp.areaid-1].depth < -1 ){
			//printf("Hand not reached area depth.\n");
			continue ;
		}

		temp.location.z = temp.origin.z = max_depth;

		blobs.push_back(temp);
	}

	// initialize previous blobs to untracked
	for (int i = 0; i < blobs_previous.size(); i++) blobs_previous[i].tracked = false;

	// main tracking loop -- O(n^2) -- simply looks for a blob in the previous frame within a specified radius
	for (int i = 0; i < blobs.size(); i++) {
		cBlob &blobi = blobs[i];
		new_hand = true;
		for (int j = 0; j < blobs_previous.size(); j++) {
			if (blobs_previous[j].tracked) continue;

			if (blobs[i].areaid == blobs_previous[j].areaid 
					&& sqrt(pow(blobs[i].location.x - blobs_previous[j].location.x, 2.0) + pow(blobs[i].location.y - blobs_previous[j].location.y, 2.0)) < max_radius) {
				blobs_previous[j].tracked = true;
				blobs[i].event = BLOB_MOVE;
				blobs[i].origin.x = history ? blobs_previous[j].origin.x : blobs_previous[j].location.x;
				blobs[i].origin.y = history ? blobs_previous[j].origin.y : blobs_previous[j].location.y;
				blobs[i].origin.z = history ? blobs_previous[j].origin.z : blobs_previous[j].location.z;

				blobs[i].handid = blobs_previous[j].handid;
				blobs[i].cursor = blobs_previous[j].cursor;
				blobs[i].cursor25D = blobs_previous[j].cursor25D;
				new_hand = false;
				break;
			}
		}
		/* assing free handid if new blob */
		if( new_hand){

			//search next free id.
			int next_handid = (last_handid+1) % MAXHANDS;//or = 0;
			while( handids[next_handid]==true && next_handid!=last_handid ){
					next_handid = (next_handid+1) % MAXHANDS;
			} //if array full -> next_handid = last_handid

			blobs[i].event = BLOB_DOWN;
			blobs[i].handid = next_handid;
			blobs[i].cursor = NULL;
			blobs[i].cursor25D = NULL;

			handids[next_handid] = true;
			last_handid = next_handid;
		}
	}

	// add any blobs from the previous frame that weren't tracked as having been removed
	for (int i = 0; i < blobs_previous.size(); i++) {
		if (!blobs_previous[i].tracked) {
			//free handid
			handids[blobs_previous[i].handid] = false;
			blobs_previous[i].event = BLOB_UP;
			blobs.push_back(blobs_previous[i]);
		}
	}
/*
	for (int i = 1; i < blob_result.GetNumBlobs(); i++) {
				current_blob = blob_result.GetBlob(i);
				printf("Blobcoordsd %f, %f\n", XCenter(current_blob), YCenter(current_blob) );
	}
*/
	int counter = 0;
	cBlob tb;
	for (int i = 0; i < blobs.size(); i++) {
			if( blobs[i].event != BLOB_UP ){
				counter++;
				tb = blobs[i];
				//printf("Blobcoordsd %f, %f\n", blobs[i].location.x, blobs[i].location.y );
				//printf("Blob areaid: %i, handid: %i, (%f,%f)\n", blobs[i].areaid, blobs[i].handid, blobs[i].location.x, blobs[i].location.y );
				cvLine(&img,
						Point((int)tb.origin.x,(int)tb.origin.y),
						Point((int)tb.location.x,(int)tb.location.y),Scalar(244),2);
				cvRectangle(&img,
						Point((int)tb.min.x,(int)tb.min.y),
						Point((int)tb.max.x,(int)tb.max.y),Scalar(255),2);
			}
	}
//	printf("Active blobs: %i %i %i\n",counter, blobs.size(), blob_result.GetNumBlobs());
/*	for(int i=0; i<MAXHANDS; i++){
		printf("%i,", (handids[i]==true)?1:0);
	}
	printf("\n");*/
}

std::vector<cBlob>& Tracker::getBlobs()
{
	return blobs;
}
