/*
 * Modification of Tracker.cpp which use an other
 * blob detection lib.
 */

#include "Tracker2.h"

Tracker2::Tracker2(double min_area, double max_area, double max_radius) : Tracker(min_area, max_area, max_radius){
	m_blob = blobtree_create();
	blobtree_set_grid(m_blob, 4,4);
	blobtree_set_filter(m_blob, F_DEPTH_MIN, 1);//depth=0 => background
	blobtree_set_filter(m_blob, F_DEPTH_MAX, 1);//depth=1 => blobs
}

Tracker2::Tracker2(SettingKinect* pSettingKinect) : Tracker(pSettingKinect)
{
	m_blob = blobtree_create();
	blobtree_set_grid(m_blob, 4,4);
	blobtree_set_filter(m_blob, F_DEPTH_MIN, 1);//depth=0 => background
	blobtree_set_filter(m_blob, F_DEPTH_MAX, 1);//depth=1 => blobs
}

Tracker2::~Tracker2()
{
	blobtree_destroy(m_blob);
	m_blob = NULL;
}

void Tracker2::trackBlobs(const Mat &mat, const Mat &areaMask, bool history, std::vector<Area> *pareas)
{
	double min_area = *m_pmin_area;
	double max_area = *m_pmax_area;
	double max_radius_2 = *m_pmax_radius * *m_pmax_radius;
	double x, y, min_x, min_y, max_x, max_y;
	double min_depth,max_depth;
	Scalar sdepth, sstddev;
	cBlob temp;
	bool new_hand(true);
	int mat_area(mat.size().width*mat.size().height);

	// we will convert the matrix object passed from our cFilter class to an object of type IplImage for calling the CBlobResult constructor
	IplImage img;
	IplImage areaImg;

	// storage of the current blobs and the blobs from the previous frame
	Size s;	Point p;
	mat.locateROI(s,p);
	areaImg = areaMask;

	// convert our OpenCV matrix object to one of type IplImage
	img = mat;

	//Gen blob tree structure
	cv::Rect *roicv = &m_pSettingKinect->m_roi;
	const uchar* ptr = mat.data;

	/*mat.data points to first entry of the ROI, not of the full matrix.
	 * => Set left and top border of roi0 to 0 and reduce height value. 
	 * */
	BlobtreeRect roi0 = {0,0,roicv->width,roicv->height };

	blobtree_find_blobs(m_blob, ptr, s.width, s.height-p.y, roi0, 1);
	blobtree_set_filter(m_blob, F_AREA_MIN, min_area);
	blobtree_set_filter(m_blob, F_AREA_MAX, max_area);

	// clear the blobs from two frames ago
	blobs_previous.clear();
	
	// before we populate the blobs vector with the current frame, we need to store the live blobs in blobs_previous
	for (int i = 0; i < blobs.size(); i++)
		if (blobs[i].event != BLOB_UP)
			blobs_previous.push_back(blobs[i]);


	// populate the blobs vector with the current frame
	blobs.clear();

	BlobtreeRect *roi;
	Node *curNode = blobtree_first(m_blob);
	while( curNode != NULL ){
		//printf("Check node %i\n", curNode->data.id);
	  roi = &curNode->data.roi;
		x     = roi->x + roi->width/2;
		y     = roi->y + roi->height/2;

//		temp.areaid = areaMask.at<uchar>((int)x+p.x,(int)y+p.y);//?!not works
		temp.areaid = (uchar) areaImg.imageData[ ((int)x+p.x) + ((int)y+p.y)*areaMask.size().width];//works
		if( temp.areaid == 0 ){
			curNode = blobtree_next(m_blob);
			continue;
		}

		min_x = roi->x; 
		min_y = roi->y;
		max_x = roi->x + roi->width;
		max_y =	roi->y + roi->height;

		/*
		 if( (max_x-min_x)*(max_y-min_y) > 0.9*mat_area){// fix blob detection issue?!
		 curNode = blobtree_next(m_blob);
		 continue;
		 }
		*/

		temp.location.x = temp.origin.x = x;
		temp.location.y = temp.origin.y = y;
		temp.min.x = min_x; temp.min.y = min_y;
		temp.max.x = max_x; temp.max.y = max_y;

		Rect r( x-3, y-3, min(7,max_x-min_x), min(7, max_y-min_y));

		/* Depth detection. The measurement method is flexible. */
		if( m_pSettingKinect->m_areaThresh ){
			/* Mean is ok, because all pixels of the blob are in front of the frame. */
			max_depth = mean( mat(r), mat(r) )[0]+4;/*correct blur(1) and area thresh shift (3)*/

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

		/* Compare depth of hand with depth of area and throw blob away if hand to far away. */
		if(pareas != NULL && max_depth - (*pareas)[temp.areaid-1].depth < -1 ){
			//printf("Hand not reached area depth.\n");
			curNode = blobtree_next(m_blob);
			continue ;
		}

		temp.location.z = temp.origin.z = max_depth;

		blobs.push_back(temp);
		curNode = blobtree_next(m_blob);
	}

	// initialize previous blobs to untracked
	float d1,d2;
	for (int i = 0; i < blobs_previous.size(); i++) blobs_previous[i].tracked = false;

	// main tracking loop -- O(n^2) -- simply looks for a blob in the previous frame within a specified radius
	for (int i = 0; i < blobs.size(); i++) {
		cBlob &blobi = blobs[i];
		new_hand = true;
		for (int j = 0; j < blobs_previous.size(); j++) {
			if (blobs_previous[j].tracked) continue;

			d1=blobs[i].location.x - blobs_previous[j].location.x;
			d2=blobs[i].location.y - blobs_previous[j].location.y;
			if (blobs[i].areaid == blobs_previous[j].areaid 
					&& (d1*d1 + d2*d2) < max_radius_2) {
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

	int counter = 0;
	cBlob tb;
	for (int i = 0; i < blobs.size(); i++) {
			if( blobs[i].event != BLOB_UP ){
				counter++;
				tb = blobs[i];
				if(true || ! *m_pnotDrawBlob ){
					cvLine(&img,
							Point((int)tb.origin.x,(int)tb.origin.y),
							Point((int)tb.location.x,(int)tb.location.y),Scalar(244),2);
					cvRectangle(&img,
							Point((int)tb.min.x,(int)tb.min.y),
							Point((int)tb.max.x,(int)tb.max.y),Scalar(255),2);
				}
			}
	}
}
