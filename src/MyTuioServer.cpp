#include <cstdio>
#include <assert.h>
#include "MyTuioServer.h"

void MyTuioServer::send_blobs(std::vector<cBlob>& blobs){

	currentTime = TuioTime::getSessionTime();
	initFrame(currentTime);

	cBlob* pb;
	for (int i = 0; i < blobs.size(); i++) {
		pb = &blobs[i];
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
					pb->cursor = addTuioCursor(pb->location.x,pb->location.y);
				}
				break;
			case BLOB_MOVE:
			default:
				{
					printf("Move cursor\n");
					assert( pb->cursor != NULL );
					updateTuioCursor(pb->cursor,pb->location.x,pb->location.y);
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
