#include <cstdio>
#include <assert.h>
#include "MyTuioServer.h"

inline long tuioSessionId(cBlob* b){
		return 1000*b->areaid+b->handid;
}

static void localCoords(cBlob *pb, Area* pa, cv::Rect* roi, float *lx, float *ly){
//	printf("Vars: (%f - (%i-%i))  / %i\n", pb->location.x, pa->rect.x, roi->x, pa->rect.width);
	float x,y;
	/*hflip coords. Where is the efficient position for flipping the whole input? convertTo? Is flip() fast?*/
	/* Map on [-1,1] */
	x = 1 - 2*(pb->location.x - pa->rect.x + roi->x ) / (float)pa->rect.width;
	y = (pb->location.y - pa->rect.y + roi->y ) / (float)pa->rect.height;

  /* Gain distanace to origin */
	if( x < 0) x = (x<0)?-1+(1+x)*(1+x):x = 1-(1-x)*(1-x);
	if( y < 0) y = (y<0)?-1+(1+y)*(1+y):y = 1-(1-y)*(1-y);

	/* Map to [0,1] */
			*lx = (x+1)/2;
			*ly = (y+1)/2;
}
void MyTuioServer::send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas, cv::Rect& roi){

	currentTime = TuioTime::getSessionTime();
	initFrame(currentTime);

	cBlob *pb;
	Area *pa;
//	printf("Area size: %i\n", areas.size());
	float lx,ly;
	for (int i = 0; i < blobs.size(); i++) {
		pb = &blobs[i];
		pa = &areas[pb->areaid-1];
		switch( pb->event ){
			case BLOB_UP:
				{
					printf("Remove cursor\n");
					assert( pb->cursor != NULL );
					removeTuioCursor(pb->cursor);
				}
				break;
			case BLOB_DOWN:
				{
					printf("Add cursor %i \n", (int)tuioSessionId(pb));
					assert( pb->cursor == NULL );
					localCoords(pb,pa,&roi,&lx,&ly);
					pb->cursor = addTuioCursor(lx,ly,tuioSessionId(pb));
				}
				break;
			case BLOB_MOVE:
			default:
				{
					localCoords(pb,pa,&roi,&lx,&ly);
					assert( pb->cursor != NULL );
					/*if( pb->cursor == NULL )
						pb->cursor = addTuioCursor(lx,ly,tuioSessionId(pb));*/
					printf("Move cursor %i to %f %f \n", (int)tuioSessionId(pb),lx,ly );
					updateTuioCursor(pb->cursor,lx,ly);
				}
				break;
		}
	}
	//processEvents();
	stopUntouchedMovingCursors();//?
	commitFrame();

/*
	if (cursor->getTuioTime()==currentTime) return;
	tuioServer->updateTuioCursor(cursor,x,y);
			cursor = tuioServer->addTuioCursor(x,y);
		tuioServer->removeTuioCursor(cursor);
	std::list<TuioCursor*> cursorList = tuioServer->getTuioCursors();
	*/
}


