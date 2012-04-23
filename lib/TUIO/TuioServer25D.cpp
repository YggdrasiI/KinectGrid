/*
	TUIO Server Component - part of the reacTIVision project
	http://reactivision.sourceforge.net/

	Copyright (c) 2005-2009 Martin Kaltenbrunner <mkalten@iua.upf.edu>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "TuioServer25D.h"

using namespace TUIO;
using namespace osc;

#ifndef WIN32
static void* ThreadFunc( void* obj )
#else
static DWORD WINAPI ThreadFunc( LPVOID obj )
#endif
{
	TuioServer25D *tuioServer = static_cast<TuioServer25D*>(obj);
	while ((tuioServer->isConnected()) && (tuioServer->periodicMessagesEnabled())) {
		tuioServer->sendFullMessages();
#ifndef WIN32
		usleep(USEC_SECOND*tuioServer->getUpdateInterval());
#else
		Sleep(MSEC_SECOND*tuioServer->getUpdateInterval());
#endif
	}	
	return 0;
};

void TuioServer25D::enablePeriodicMessages(int interval) {
	if (periodic_update) return;
	
	update_interval = interval;
	periodic_update = true;
	
#ifndef WIN32
	pthread_create(&thread , NULL, ThreadFunc, this);
#else
	DWORD threadId;
	thread = CreateThread( 0, 0, ThreadFunc, this, 0, &threadId );
#endif
}

void TuioServer25D::disablePeriodicMessages() {
	if (!periodic_update) return;
	periodic_update = false;
	
#ifdef WIN32
	if( thread ) CloseHandle( thread );
#endif
	thread = NULL;	
}

void TuioServer25D::sendFullMessages() {
	
	// prepare the cursor packet
	fullPacket->Clear();
	(*fullPacket) << osc::BeginBundleImmediate;
	
	// add the cursor alive message
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
	for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++)
		(*fullPacket) << (int32)((*tuioCursor)->getSessionID());	
	(*fullPacket) << osc::EndMessage;	

	// add all current cursor set messages
	for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		
		// start a new packet if we exceed the packet capacity
		if ((fullPacket->Capacity()-fullPacket->Size())<CUR_MESSAGE_SIZE) {
			
			// add the immediate fseq message and send the cursor packet
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
			(*fullPacket) << osc::EndBundle;
			socket->Send( fullPacket->Data(), fullPacket->Size() );

			// prepare the new cursor packet
			fullPacket->Clear();	
			(*fullPacket) << osc::BeginBundleImmediate;
			
			// add the cursor alive message
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
			for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++)
				(*fullPacket) << (int32)((*tuioCursor)->getSessionID());	
			(*fullPacket) << osc::EndMessage;				
		}

		// add the actual cursor set message
		(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "set";
		(*fullPacket) << (int32)((*tuioCursor)->getSessionID()) << (*tuioCursor)->getX() << (*tuioCursor)->getY() << (*tuioCursor)->getZ();
		(*fullPacket) << (*tuioCursor)->getXSpeed() << (*tuioCursor)->getYSpeed() << (*tuioCursor)->getZSpeed() <<(*tuioCursor)->getMotionAccel();	
		(*fullPacket) << osc::EndMessage;	
	}
	
	// add the immediate fseq message and send the cursor packet
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
	(*fullPacket) << osc::EndBundle;
	socket->Send( fullPacket->Data(), fullPacket->Size() );
	
	// prepare the object packet
	fullPacket->Clear();
	(*fullPacket) << osc::BeginBundleImmediate;
	
	// add the object alive message
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
	for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++)
		(*fullPacket) << (int32)((*tuioObject)->getSessionID());	
	(*fullPacket) << osc::EndMessage;	

	for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		
		// start a new packet if we exceed the packet capacity
		if ((fullPacket->Capacity()-fullPacket->Size())<OBJ_MESSAGE_SIZE) {
			// add the immediate fseq message and send the object packet
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
			(*fullPacket) << osc::EndBundle;
			socket->Send( fullPacket->Data(), fullPacket->Size() );
			
			// prepare the new object packet
			fullPacket->Clear();	
			(*fullPacket) << osc::BeginBundleImmediate;
			
			// add the object alive message
			(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
			for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++)
				(*fullPacket) << (int32)((*tuioObject)->getSessionID());	
			(*fullPacket) << osc::EndMessage;	
		}

		// add the actual object set message
		(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "set";
		(*fullPacket) << (int32)((*tuioObject)->getSessionID()) << (*tuioObject)->getSymbolID() << (*tuioObject)->getX() << (*tuioObject)->getY() << (*tuioObject)->getZ() << (*tuioObject)->getAngle();
		(*fullPacket) << (*tuioObject)->getXSpeed() << (*tuioObject)->getYSpeed() << (*tuioObject)->getZSpeed() << (*tuioObject)->getRotationSpeed() << (*tuioObject)->getMotionAccel() << (*tuioObject)->getRotationAccel();	
		(*fullPacket) << osc::EndMessage;
		
	}
	// add the immediate fseq message and send the object packet
	(*fullPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
	(*fullPacket) << osc::EndBundle;
	socket->Send( fullPacket->Data(), fullPacket->Size() );
}

TuioServer25D::TuioServer25D() {
	initialize("127.0.0.1",3333,MAX_UDP_SIZE);
}

TuioServer25D::TuioServer25D(const char *host, int port) {
	initialize(host,port,IP_MTU_SIZE);
}

TuioServer25D::TuioServer25D(const char *host, int port, int size) {
	initialize(host,port,size);
}

void TuioServer25D::initialize(const char *host, int port, int size) {
	if (size>MAX_UDP_SIZE) size = MAX_UDP_SIZE;
	else if (size<MIN_UDP_SIZE) size = MIN_UDP_SIZE;

	try {
		long unsigned int ip = GetHostByName(host);
		socket = new UdpTransmitSocket(IpEndpointName(ip, port));

		oscBuffer = new char[size];
		oscPacket = new osc::OutboundPacketStream(oscBuffer,size);
		fullBuffer = new char[size];
		fullPacket = new osc::OutboundPacketStream(fullBuffer,size);
	} catch (std::exception &e) { 
		std::cout << "could not create socket" << std::endl;
		socket = NULL;
	}
	
	currentFrameTime = TuioTime::getSessionTime().getSeconds();
	currentFrame = sessionID = maxCursorID = -1;
	verbose = updateObject = updateCursor = false;
	lastObjectUpdate = lastCursorUpdate = currentFrameTime.getSeconds();
	
	sendEmptyCursorBundle();
	sendEmptyObjectBundle();

	periodic_update = false;
	full_update = false;
	connected = true;
}

TuioServer25D::~TuioServer25D() {
	connected = false;

	sendEmptyCursorBundle();
	sendEmptyObjectBundle();

	delete oscPacket;
	delete []oscBuffer;
	delete fullPacket;
	delete []fullBuffer;
	delete socket;
}


TuioObject25D* TuioServer25D::addTuioObject(int f_id, float x, float y, float z, float a) {
	sessionID++;
	TuioObject25D *tobj = new TuioObject25D(currentFrameTime, sessionID, f_id, x, y, z, a);
	objectList.push_back(tobj);
	updateObject = true;

	if (verbose)
		std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getZ() << " " << tobj->getZ() << " " << tobj->getAngle() << std::endl;

	return tobj;
}

void TuioServer25D::addExternalTuioObject25D(TuioObject25D *tobj) {
	if (tobj==NULL) return;
	objectList.push_back(tobj);
	updateObject = true;
	
	if (verbose)
		std::cout << "add obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getZ() << " " << tobj->getZ() << " " << tobj->getAngle() << std::endl;
}

void TuioServer25D::updateTuioObject(TuioObject25D *tobj, float x, float y, float z, float a) {
	if (tobj==NULL) return;
	if (tobj->getTuioTime()==currentFrameTime) return;
	tobj->update(currentFrameTime,x,y,z,a);
	updateObject = true;

	if (verbose && tobj->isMoving())		
		std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getZ() << " " << tobj->getZ() << " " << tobj->getAngle() 
		<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getZSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;	
}

void TuioServer25D::updateExternalTuioObject25D(TuioObject25D *tobj) {
	if (tobj==NULL) return;
	updateObject = true;
	if (verbose && tobj->isMoving())	
		std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getZ() << " " << tobj->getAngle() 
		<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getZSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;	
}

void TuioServer25D::removeTuioObject(TuioObject25D *tobj) {
	if (tobj==NULL) return;
	objectList.remove(tobj);
	delete tobj;
	updateObject = true;
	
	if (verbose)
		std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}

void TuioServer25D::removeExternalTuioObject25D(TuioObject25D *tobj) {
	if (tobj==NULL) return;
	objectList.remove(tobj);
	updateObject = true;
	
	if (verbose)
		std::cout << "del obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ")" << std::endl;
}


TuioCursor25D* TuioServer25D::addTuioCursor(float x, float y, float z) {
	sessionID++;
	return addTuioCursor(x,y,z,sessionID);
}

TuioCursor25D* TuioServer25D::addTuioCursor(float x, float y, float z, long _sessionID) {
	
	int cursorID = (int)cursorList.size();
	if (((int)(cursorList.size())<=maxCursorID) && ((int)(freeCursorList.size())>0)) {
		std::list<TuioCursor25D*>::iterator closestCursor = freeCursorList.begin();
		
		for(std::list<TuioCursor25D*>::iterator iter = freeCursorList.begin();iter!= freeCursorList.end(); iter++) {
			if((*iter)->getDistance(x,y,z)<(*closestCursor)->getDistance(x,y,z)) closestCursor = iter;
		}
		
		TuioCursor25D *freeCursor = (*closestCursor);
		cursorID = (*closestCursor)->getCursorID();
		freeCursorList.erase(closestCursor);
		delete freeCursor;
	} else maxCursorID = cursorID;	
	
	TuioCursor25D *tcur = new TuioCursor25D(currentFrameTime, _sessionID, cursorID, x, y, z);
	cursorList.push_back(tcur);
	updateCursor = true;

	if (verbose) 
		std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << " " << tcur->getZ() << std::endl;

	return tcur;
}

void TuioServer25D::addExternalTuioCursor25D(TuioCursor25D *tcur) {
	if (tcur==NULL) return;
	cursorList.push_back(tcur);
	updateCursor = true;
	
	if (verbose) 
		std::cout << "add cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << " " << tcur->getZ() << std::endl;
}

void TuioServer25D::updateTuioCursor(TuioCursor25D *tcur,float x, float y, float z) {
	if (tcur==NULL) return;
	if (tcur->getTuioTime()==currentFrameTime) return;
	tcur->update(currentFrameTime,x,y,z);
	updateCursor = true;

	if (verbose && tcur->isMoving())	 	
		std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << " " << tcur->getZ() 
		<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed() << " " << tcur->getZSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void TuioServer25D::updateExternalTuioCursor25D(TuioCursor25D *tcur) {
	if (tcur==NULL) return;
	updateCursor = true;
	if (verbose && tcur->isMoving())		
		std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << " " << tcur->getZ() 
		<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed() << " " << tcur->getZSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;
}

void TuioServer25D::removeTuioCursor(TuioCursor25D *tcur) {
	if (tcur==NULL) return;
	cursorList.remove(tcur);
	tcur->remove(currentFrameTime);
	updateCursor = true;

	if (verbose)
		std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;

	if (tcur->getCursorID()==maxCursorID) {
		maxCursorID = -1;
		delete tcur;
		
		if (cursorList.size()>0) {
			std::list<TuioCursor25D*>::iterator clist;
			for (clist=cursorList.begin(); clist != cursorList.end(); clist++) {
				int cursorID = (*clist)->getCursorID();
				if (cursorID>maxCursorID) maxCursorID=cursorID;
			}
			
			freeCursorBuffer.clear();
			for (std::list<TuioCursor25D*>::iterator flist=freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
				TuioCursor25D *freeCursor = (*flist);
				if (freeCursor->getCursorID()>maxCursorID) delete freeCursor;
				else freeCursorBuffer.push_back(freeCursor);
			}
			freeCursorList = freeCursorBuffer;
			
		} else {
			for (std::list<TuioCursor25D*>::iterator flist=freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
				TuioCursor25D *freeCursor = (*flist);
				delete freeCursor;
			}
			freeCursorList.clear();
		} 
	} else if (tcur->getCursorID()<maxCursorID) {
		freeCursorList.push_back(tcur);
	}
}

void TuioServer25D::removeExternalTuioCursor25D(TuioCursor25D *tcur) {
	if (tcur==NULL) return;
	cursorList.remove(tcur);
	updateCursor = true;
	
	if (verbose)
		std::cout << "del cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ")" << std::endl;
}

long TuioServer25D::getSessionID() {
	sessionID++;
	return sessionID;
}

long TuioServer25D::getFrameID() {
	return currentFrame;
}

TuioTime TuioServer25D::getFrameTime() {
	return currentFrameTime;
}

void TuioServer25D::initFrame(TuioTime ttime) {
	currentFrameTime = ttime;
	currentFrame++;
}

void TuioServer25D::commitFrame() {
	
	if(updateCursor) {
		startCursorBundle();
		for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
			
			// start a new packet if we exceed the packet capacity
			if ((oscPacket->Capacity()-oscPacket->Size())<CUR_MESSAGE_SIZE) {
				sendCursorBundle(currentFrame);
				startCursorBundle();
			}

			TuioCursor25D *tcur = (*tuioCursor);
			if ((full_update) || (tcur->getTuioTime()==currentFrameTime)) addCursorMessage(tcur);				
		}
		sendCursorBundle(currentFrame);
	} else if ((!periodic_update) && (lastCursorUpdate<currentFrameTime.getSeconds())) {
		lastCursorUpdate = currentFrameTime.getSeconds();
		startCursorBundle();
		sendCursorBundle(currentFrame);
	}
	updateCursor = false;
	
	if(updateObject) {
		startObjectBundle();
		for (std::list<TuioObject25D*>::iterator  tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
			
			// start a new packet if we exceed the packet capacity
			if ((oscPacket->Capacity()-oscPacket->Size())<OBJ_MESSAGE_SIZE) {
				sendObjectBundle(currentFrame);
				startObjectBundle();
			}
			
			TuioObject25D *tobj = (*tuioObject);
			if  ((full_update) || (tobj->getTuioTime()==currentFrameTime)) addObjectMessage(tobj);
		} 
		sendObjectBundle(currentFrame);
	} else if ((!periodic_update) && (lastObjectUpdate<currentFrameTime.getSeconds())) {
		lastObjectUpdate = currentFrameTime.getSeconds();
		startObjectBundle();
		sendObjectBundle(currentFrame);
	}
	updateObject = false;
}

void TuioServer25D::sendEmptyCursorBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive" << osc::EndMessage;	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << -1 << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer25D::startCursorBundle() {	
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "alive";
	for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		(*oscPacket) << (int32)((*tuioCursor)->getSessionID());	
	}
	(*oscPacket) << osc::EndMessage;	
}

void TuioServer25D::addCursorMessage(TuioCursor25D *tcur) {

	 (*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "set";
	 (*oscPacket) << (int32)(tcur->getSessionID()) << tcur->getX() << tcur->getY() << tcur->getZ();
	 (*oscPacket) << tcur->getXSpeed() << tcur->getYSpeed() << tcur->getZSpeed() << tcur->getMotionAccel();	
	 (*oscPacket) << osc::EndMessage;
}

void TuioServer25D::sendCursorBundle(long fseq) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dcur") << "fseq" << (int32)fseq << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer25D::sendEmptyObjectBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive" << osc::EndMessage;	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << -1 << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

void TuioServer25D::startObjectBundle() {
	oscPacket->Clear();	
	(*oscPacket) << osc::BeginBundleImmediate;
	
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "alive";
	for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		(*oscPacket) << (int32)((*tuioObject)->getSessionID());	
	}
	(*oscPacket) << osc::EndMessage;	
}

void TuioServer25D::addObjectMessage(TuioObject25D *tobj) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "set";
	(*oscPacket) << (int32)(tobj->getSessionID()) << tobj->getSymbolID() << tobj->getX() << tobj->getY() << tobj->getZ() << tobj->getAngle();
	(*oscPacket) << tobj->getXSpeed() << tobj->getYSpeed() << tobj->getZSpeed() << tobj->getRotationSpeed() << tobj->getMotionAccel() << tobj->getRotationAccel();	
	(*oscPacket) << osc::EndMessage;
}

void TuioServer25D::sendObjectBundle(long fseq) {
	(*oscPacket) << osc::BeginMessage( "/tuio/2Dobj") << "fseq" << (int32)fseq << osc::EndMessage;
	(*oscPacket) << osc::EndBundle;
	socket->Send( oscPacket->Data(), oscPacket->Size() );
}

TuioObject25D* TuioServer25D::getTuioObject25D(long s_id) {
	for (std::list<TuioObject25D*>::iterator iter=objectList.begin(); iter != objectList.end(); iter++)
		if((*iter)->getSessionID()==s_id) return (*iter);
	
	return NULL;
}

TuioCursor25D* TuioServer25D::getTuioCursor25D(long s_id) {
	for (std::list<TuioCursor25D*>::iterator iter=cursorList.begin(); iter != cursorList.end(); iter++)
		if((*iter)->getSessionID()==s_id) return (*iter);
	
	return NULL;
}

TuioObject25D* TuioServer25D::getClosestTuioObject25D(float xp, float yp, float zp) {
	
	TuioObject25D *closestObject = NULL;
	float closestDistance = 1.0f;
	
	for (std::list<TuioObject25D*>::iterator iter=objectList.begin(); iter != objectList.end(); iter++) {
		float distance = (*iter)->getDistance(xp,yp,zp);
		if(distance<closestDistance) {
			closestObject = (*iter);
			closestDistance = distance;
		}
	}
	
	return closestObject;
}

TuioCursor25D* TuioServer25D::getClosestTuioCursor25D(float xp, float yp, float zp) {

	TuioCursor25D *closestCursor = NULL;
	float closestDistance = 1.0f;

	for (std::list<TuioCursor25D*>::iterator iter=cursorList.begin(); iter != cursorList.end(); iter++) {
		float distance = (*iter)->getDistance(xp,yp,zp);
		if(distance<closestDistance) {
			closestCursor = (*iter);
			closestDistance = distance;
		}
	}
	
	return closestCursor;
}

std::list<TuioObject25D*> TuioServer25D::getTuioObject25Ds() {
	return objectList;
}

std::list<TuioCursor25D*> TuioServer25D::getTuioCursor25Ds() {
	return cursorList;
}

std::list<TuioObject25D*> TuioServer25D::getUntouchedObjects() {
	
	std::list<TuioObject25D*> untouched;
	for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		TuioObject25D *tobj = (*tuioObject);
		if (tobj->getTuioTime()!=currentFrameTime) untouched.push_back(tobj);
	}	
	return untouched;
}

void TuioServer25D::stopUntouchedMovingObjects() {
	
	std::list<TuioObject25D*> untouched;
	for (std::list<TuioObject25D*>::iterator tuioObject = objectList.begin(); tuioObject!=objectList.end(); tuioObject++) {
		
		TuioObject25D *tobj = (*tuioObject);
		if ((tobj->getTuioTime()!=currentFrameTime) && (tobj->isMoving())) {
			tobj->stop(currentFrameTime);
			updateObject = true;
			if (verbose)		
				std::cout << "set obj " << tobj->getSymbolID() << " (" << tobj->getSessionID() << ") "<< tobj->getX() << " " << tobj->getY() << " " << tobj->getZ() << " " << tobj->getAngle() 
				<< " " << tobj->getXSpeed() << " " << tobj->getYSpeed() << " " << tobj->getZSpeed() << " " << tobj->getRotationSpeed() << " " << tobj->getMotionAccel() << " " << tobj->getRotationAccel() << std::endl;
		}
	}
}

void TuioServer25D::removeUntouchedStoppedObjects() {
	
	std::list<TuioObject25D*>::iterator tuioObject = objectList.begin();
	while (tuioObject!=objectList.end()) {
		TuioObject25D *tobj = (*tuioObject);
		if ((tobj->getTuioTime()!=currentFrameTime) && (!tobj->isMoving())) {
			removeTuioObject(tobj);
			tuioObject = objectList.begin();
		} else tuioObject++;
	}
}


std::list<TuioCursor25D*> TuioServer25D::getUntouchedCursors() {
	
	std::list<TuioCursor25D*> untouched;
	for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		TuioCursor25D *tcur = (*tuioCursor);
		if (tcur->getTuioTime()!=currentFrameTime) untouched.push_back(tcur);
	}	
	return untouched;
}

void TuioServer25D::stopUntouchedMovingCursors() {
	
	std::list<TuioCursor25D*> untouched;
	for (std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin(); tuioCursor!=cursorList.end(); tuioCursor++) {
		TuioCursor25D *tcur = (*tuioCursor);
		if ((tcur->getTuioTime()!=currentFrameTime) && (tcur->isMoving())) {
			tcur->stop(currentFrameTime);
			updateCursor = true;
			if (verbose) 	
				std::cout << "set cur " << tcur->getCursorID() << " (" <<  tcur->getSessionID() << ") " << tcur->getX() << " " << tcur->getY() << " " << tcur->getZ() 
				<< " " << tcur->getXSpeed() << " " << tcur->getYSpeed() << " " << tcur->getZSpeed() << " " << tcur->getMotionAccel() << " " << std::endl;							
		}
	}	
}

void TuioServer25D::removeUntouchedStoppedCursors() {
	
	if (cursorList.size()==0) return;
	std::list<TuioCursor25D*>::iterator tuioCursor = cursorList.begin();
	while (tuioCursor!=cursorList.end()) {
		TuioCursor25D *tcur = (*tuioCursor);
		if ((tcur->getTuioTime()!=currentFrameTime) && (!tcur->isMoving())) {
			removeTuioCursor(tcur);
			tuioCursor = cursorList.begin();
		} else tuioCursor++;
	}	
}
