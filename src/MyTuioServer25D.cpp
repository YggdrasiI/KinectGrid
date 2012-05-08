#include <cstdio>
#include <assert.h>
#include "MyTuioServer25D.h"

inline long tuioSessionId(cBlob* b){
		return 1000*b->areaid+b->handid;
}

static void localCoords(cBlob *pb, Area* pa, cv::Rect* roi, float *lx, float *ly, float *lz){
//	printf("Vars: (%f - (%i-%i))  / %i\n", pb->location.x, pa->rect.x, roi->x, pa->rect.width);
	float x,y,z;
	/*hflip coords. Where is the efficient position for flipping the whole input? convertTo? Is flip() fast?*/
	/* Map on [-1,1] */
	x = 1 - 2*(pb->location.x - pa->rect.x + roi->x ) / (float)pa->rect.width;
	y = 1 - 2*(pb->location.y - pa->rect.y + roi->y ) / (float)pa->rect.height;

  /* Gain distanace to origin */
	x = (x<0)?-1+(1+x)*(1+x):x = 1-(1-x)*(1-x);
	y = (y<0)?-1+(1+y)*(1+y):y = 1-(1-y)*(1-y);

	/* Map to [0,1) */
			*lx = min( (x+1)/2, 0.99999 );
			*ly = min( (y+1)/2, 0.99999 );

	/* Depth */
	z = (pb->location.z - pa->depth)/25.0/*100.0*/;
	*lz = (z<0)?0:((z<1)?z:1);
}
void MyTuioServer25D::send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi){

	currentTime = TuioTime::getSessionTime();
	initFrame(currentTime);

	cBlob *pb;
	Area *pa;
//	printf("Area size: %i\n", areas.size());
	float lx,ly,lz;
	for (int i = 0; i < blobs.size(); i++) {
		pb = &blobs[i];
		pa = &areas[pb->areaid-1];
		switch( pb->event ){
			case BLOB_UP:
				{
					//printf("Remove cursor25D\n");
					//assert( pb->cursor25D != NULL );
					if( pb->cursor25D == NULL ) break;
					removeTuioCursor(pb->cursor25D);
				}
				break;
			case BLOB_DOWN:
				{
					localCoords(pb,pa,&roi,&lx,&ly,&lz);
					//assert( pb->cursor25D == NULL );
					if( pb->cursor25D == NULL ){
						pb->cursor25D = addTuioCursor(lx,ly,lz,tuioSessionId(pb));
						//printf("(1)Add cursor25D %i \n", (int)tuioSessionId(pb));
					}else{
						//printf("(1)Move cursor25D %i to %f %f %f \n", (int)tuioSessionId(pb),lx,ly,lz );
						updateTuioCursor(pb->cursor25D,lx,ly,lz);
					}
				}
				break;
			case BLOB_MOVE:
			default:
				{
					localCoords(pb,pa,&roi,&lx,&ly,&lz);
					//assert( pb->cursor25D != NULL );
					if( pb->cursor25D == NULL ){
						//printf("(2)Add cursor25D %i \n", (int)tuioSessionId(pb));
						pb->cursor25D = addTuioCursor(lx,ly,lz,tuioSessionId(pb));
					}else{
						//printf("(2)Move cursor25D %i to %f %f %f \n", (int)tuioSessionId(pb),lx,ly,lz );
						updateTuioCursor(pb->cursor25D,lx,ly,lz);
					}
				}
				break;
		}
	}
	//processEvents();
	stopUntouchedMovingCursors();//?
	commitFrame();

/*
	if (cursor25D->getTuioTime()==currentTime) return;
	tuioServer->updateTuioCursor(cursor25D,x,y);
			cursor25D = tuioServer->addTuioCursor(x,y);
		tuioServer->removeTuioCursor(cursor25D);
	std::list<TuioCursor*> cursorList = tuioServer->getTuioCursors();
	*/
}


