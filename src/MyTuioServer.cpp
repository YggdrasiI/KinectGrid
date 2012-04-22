#include <cstdio>
#include <assert.h>
#include "MyTuioServer.h"

inline long tuioSessionId(cBlob* b){
		return 1000*b->areaid+b->handid;
}

static void localCoords(cBlob *pb, Area* pa, float *lx, float *ly){
	*lx = (pb->location.x - pa->rect.x) / pa->rect.width;
	*ly = (pb->location.y - pa->rect.y) / pa->rect.height;
}
void MyTuioServer::send_blobs(std::vector<cBlob>& blobs, std::vector<Area>& areas){

	currentTime = TuioTime::getSessionTime();
	initFrame(currentTime);

	cBlob *pb;
	Area *pa;
	float lx,ly;
	for (int i = 0; i < blobs.size(); i++) {
		pb = &blobs[i];
		pa = &areas[pb->areaid];
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
					printf("Add cursor\n");
					assert( pb->cursor == NULL );
					localCoords(pb,pa,&lx,&ly);
					pb->cursor = addTuioCursor(lx,ly,tuioSessionId(pb));
				}
				break;
			case BLOB_MOVE:
			default:
				{
					printf("Move cursor\n");
					assert( pb->cursor != NULL );
					localCoords(pb,pa,&lx,&ly);
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



