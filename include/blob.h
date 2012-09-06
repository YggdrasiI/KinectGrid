#ifndef BLOB_H
#define BLOB_H

#include "TuioCursor.h"
#include "TuioCursor25D.h"

enum { BLOB_NULL, BLOB_DOWN, BLOB_MOVE, BLOB_UP }; // event types

struct point {
	float x, y;//avoid double for ARM?
	float z; //depth
};

class cBlob {
  private:

  protected:

  public:
	point location, origin;	// current location and origin for defining a drag vector
	point min, max;		// to define our axis-aligned bounding box
	int event;		// event type: one of BLOB_NULL, BLOB_DOWN, BLOB_MOVE, BLOB_UP
	bool tracked;		// a flag to indicate this blob has been processed
	int handid; // associate id for tuio processing
	int areaid; 
	TUIO::TuioCursor *cursor;
	TUIO::TuioCursor25D *cursor25D;
	point back; // backup location before get_tip_pos search (weighted) barycenter of blob. (testing...)
};

#endif
