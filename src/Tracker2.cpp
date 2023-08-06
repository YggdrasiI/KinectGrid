/*
 * Modification of Tracker.cpp which use an other
 * blob detection lib.
 */

#include "Tracker2.h"

Tracker2::Tracker2(double min_area, double max_area, double max_radius) :
	Tracker(min_area, max_area, max_radius),
	m_workspace(NULL),
	m_blob(NULL)
{
  threshtree_create_workspace( KRES_X, KRES_Y, &m_workspace );
	blobtree_create(&m_blob);
	blobtree_set_grid(m_blob, 2,2);
	blobtree_set_filter(m_blob, Blob::F_TREE_DEPTH_MIN, 1);//depth=0 => background
	blobtree_set_filter(m_blob, Blob::F_TREE_DEPTH_MAX, 1);//depth=1 => blobs
}

Tracker2::Tracker2(SettingKinect* pSettingKinect) :
	Tracker(pSettingKinect),
	m_workspace(NULL),
	m_blob(NULL)
{
  threshtree_create_workspace( KRES_X, KRES_Y, &m_workspace );
	blobtree_create(&m_blob);
	blobtree_set_grid(m_blob, 2,2);
	blobtree_set_filter(m_blob, Blob::F_TREE_DEPTH_MIN, 1);//depth=0 => background
	blobtree_set_filter(m_blob, Blob::F_TREE_DEPTH_MAX, 1);//depth=1 => blobs
}

Tracker2::~Tracker2()
{
	blobtree_destroy(&m_blob);
  threshtree_destroy_workspace( &m_workspace );
}

void Tracker2::trackBlobs(const cv::Mat &mat, const cv::Mat &areaMask, bool history, std::vector<Area> *pareas)
{
	double min_area = *m_pmin_area;
	double max_area = *m_pmax_area;
	double max_radius_2 = *m_pmax_radius * *m_pmax_radius;
	//double x, y, min_x, min_y, max_x, max_y;
	//double min_depth,max_depth;
	int x, y, min_x, min_y, max_x, max_y;
	int min_depth,max_depth;
	cv::Scalar sdepth, sstddev;
	cBlob temp;
	bool new_hand(true);
	int mat_area(mat.size().width*mat.size().height);

	// storage of the current blobs and the blobs from the previous frame
	
	//Gen blob tree structure
	cv::Rect *roicv = &m_pSettingKinect->m_kinectProp.roi;
	const uchar* ptr = mat.data;

  if( ptr == NULL ){
		VPRINT("(Tracker2) No image data available. Region of intrest was (%d, %d, %d, %d) \n",
        roicv->x, roicv->y, roicv->width, roicv->height);
    return;
  }

	// mat could be a submatrix, but areaMask has complete range.
	// we need the offset information of mat to compare pixels of mat with areaMask.
	cv::Size parentMatSize;	cv::Point parentMatPoint;
	mat.locateROI(parentMatSize,parentMatPoint);

	/*mat.data points to first entry of the ROI, not of the full matrix.
	 * => Set left and top border of roi0 to 0 and reduce height value. 
	 * */
	Blob::BlobtreeRect roi0 = {0,0,roicv->width,roicv->height };

	Blob::threshtree_find_blobs(m_blob, ptr, parentMatSize.width, parentMatSize.height-parentMatPoint.y, roi0, 1, m_workspace);
	Blob::blobtree_set_filter(m_blob, Blob::F_AREA_MIN, min_area);
	Blob::blobtree_set_filter(m_blob, Blob::F_AREA_MAX, max_area);

	// clear the blobs from two frames ago
	blobs_previous.clear();
	
	// before we populate the blobs vector with the current frame, we need to store the live blobs in blobs_previous
	for (int i = 0; i < blobs.size(); i++)
		if (blobs[i].event != BLOB_UP)
			blobs_previous.push_back(blobs[i]);


	// populate the blobs vector with the current frame
	blobs.clear();

	Blob::BlobtreeRect *roi;
	Blob::Node *curNode = blobtree_first(m_blob);
	while( curNode != NULL ){
		//printf("Check node %i\n", curNode->data.id);
	  roi = &((Blob::Blob*)curNode->data)->roi;
#ifdef BLOB_BARYCENTER
		x     = ((Blob::Blob*)curNode->data)->barycenter[0];
		y     = ((Blob::Blob*)curNode->data)->barycenter[1];
#else
		x     = roi->x + roi->width/2;
		y     = roi->y + roi->height/2;
#endif

#ifndef NDEBUG
		printf("(x, p.x; y, p.y)=(%.3f, %i, %.3f, %i)\n",
				x, parentMatPoint.x,
				y, parentMatPoint.y);

		// Translate (y,x)-position of submatrix in index of full matrix.
		const int fullmatrixPixelPos = ((int)y+parentMatPoint.y) * parentMatSize.width + ((int)x+parentMatPoint.x);
		const int submatrixPixelPos = ((int)y) * mat.size().width + ((int)x);
		if (0 > submatrixPixelPos || submatrixPixelPos >= mat_area) {
			printf("Error: Blob center position outside of image?!\n"
					"Local index: %i\n"
					"Local position: (%i, y=%i)\n",
					submatrixPixelPos,
					(int)(x), (int)(y));
		}
		if (0 > fullmatrixPixelPos || fullmatrixPixelPos >= areaMask.size().width * areaMask.size().height) {
			printf("Error: Blob center position outside of areaMask?!\n"
					"Global index: %i\n"
					"Local position: (%i, %i)\n"
					"Position inside of mask: (%i, %i)\n"
					"Mask dimension: (%i, %i)",
					fullmatrixPixelPos,
					(int)(x), (int)(y),
					(int)(x+parentMatPoint.x), (int)(y+parentMatPoint.y),
					areaMask.size().width, areaMask.size().height);
			curNode = blobtree_next(m_blob);
			continue;
		}

		/*int areaid1 = areaMask.at<uchar>((int)(y) + parentMatPoint.y, (int)(x) + parentMatPoint.x);// row/y, column/x order
		int areaid2 = ((uchar *) areaMask.data)[fullmatrixPixelPos];
		printf("Vergleich: %s %i %i\n", areaid1==areaid2?"":"NEIN", areaid1, areaid2);
		*/
#endif

		//temp.areaid = areaMask.at<uchar>((int)(y) + parentMatPoint.y, (int)(x) + parentMatPoint.x);// row/y, column/x order
		// or
		const uchar* am = &areaMask.at<uchar>(0);
		temp.areaid = am[fullmatrixPixelPos];

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

#ifdef CENTER_ADJUSTMENT
		//Improved Detection of blob midpoint require big rect.
		cv::Rect r(roi->x,roi->y,roi->width,roi->height);
#else
		cv::Rect r( x-3, y-3, min(7,max_x-min_x), min(7, max_y-min_y));
#endif

		cv::Mat matR = mat(r);

#ifdef CENTER_ADJUSTMENT
		/* Approximante position of tip of Blob
		 * */
		temp.back.x = x;
		temp.back.y = y;

		uint8_t thresh;
		if( m_pSettingKinect->m_kinectProp.areaThresh ){
			//Do not use constant thresh. matR already includes this (pointwise) information.
			thresh = 0;
		}else if( pareas != NULL){
			//use depthvalue of area as thresh.
			thresh = (*pareas)[temp.areaid-1].depth-2;
			if(thresh>252) thresh=0; 
		}else{
			//use general back value as thresh.
			thresh =  m_pSettingKinect->m_kinectProp.marginBack;
		}
		get_tip(r, matR, thresh, &x, &y, &max_depth);
		printf("TIP: %f %f %f\n", x, y, max_depth);

		/* Compare depth of hand with depth of area and throw blob away if hand to far away. */
		if(pareas != NULL && max_depth - (*pareas)[temp.areaid-1].depth < -1 ){
			printf("Hand not reached area depth.\n");
			curNode = blobtree_next(m_blob);
			continue ;
		}

		temp.location.x = temp.origin.x = x;
		temp.location.y = temp.origin.y = y;
		temp.location.z = temp.origin.z = max_depth;

		printf("L: %f %f C: %f %f \n",temp.location.x,temp.location.y,temp.back.x,temp.back.y);

#else

		temp.location.x = temp.origin.x = x;
		temp.location.y = temp.origin.y = y;

		/* Depth detection. The measurement method is flexible. */
		if( m_pSettingKinect->m_kinectProp.areaThresh ){
			/* Mean is ok, because all pixels of the blob are in front of the frame. */
			max_depth = mean( matR, matR )[0]+4;/*correct blur(1) and area thresh shift (3)*/

		}else	if( pareas != NULL){
			/* Remove values behind the area depth and count mean of rest.
				This is problematic/choppy if to many pixels are removed.
			*/
			max_depth = max( (*pareas)[temp.areaid-1].depth-22, 
					mean( matR, matR>(*pareas)[temp.areaid-1].depth-2 )[0] + 1);

		}else{
			/* Very few information. Use maximum of blob. (Choppy).
			 * Can be improved, if mean of i.e. 10 biggest values is used
			 * minMaxLoc require filtered/blured images.
			 * */
			//max_depth = 0;
			minMaxLoc( matR, &min_depth, &max_depth, NULL, NULL, matR );
		}


		/* Compare depth of hand with depth of area and throw blob away if hand to far away. */
		if(pareas != NULL && max_depth - (*pareas)[temp.areaid-1].depth < -1 ){
			//printf("Hand not reached area depth.\n");
			curNode = blobtree_next(m_blob);
			continue ;
		}
		temp.location.z = temp.origin.z = max_depth;
#endif

		temp.min.x = min_x; temp.min.y = min_y;
		temp.max.x = max_x; temp.max.y = max_y;

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
					cv::line(mat,
							cv::Point((int)tb.origin.x,(int)tb.origin.y),
							cv::Point((int)tb.location.x,(int)tb.location.y),cv::Scalar(230),2);
					cv::rectangle(mat,
							cv::Point((int)tb.min.x,(int)tb.min.y),
							cv::Point((int)tb.max.x,(int)tb.max.y),cv::Scalar(255),2);
					/**/
					//test barycenter
					cv::rectangle(mat,
							cv::Point((int)tb.min.x,(int)tb.min.y),
							cv::Point((int)tb.max.x,(int)tb.max.y),cv::Scalar(50),-1);
					cv::rectangle(mat,
							cv::Point((int)tb.back.x-2,(int)tb.back.y-2),
							cv::Point((int)tb.back.x+2,(int)tb.back.y+2),cv::Scalar(200),2);
					cv::rectangle(mat,
							cv::Point((int)tb.location.x-2,(int)tb.location.y-2),
							cv::Point((int)tb.location.x+2,(int)tb.location.y+2),cv::Scalar(250),2);
					/**/
				}
			}
	}
}

