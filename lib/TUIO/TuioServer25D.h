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

#ifndef INCLUDED_TuioServer25D25D_H
#define INCLUDED_TuioServer25D25D_H

#ifndef WIN32
#include <pthread.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif

#include <iostream>
#include <list>
#include <algorithm>

#include "osc/OscOutboundPacketStream.h"
#include "ip/NetworkingUtils.h"
#include "ip/UdpSocket.h"

#include "TuioObject25D.h"
#include "TuioCursor25D.h"

#define IP_MTU_SIZE 1500
#define MAX_UDP_SIZE 65536
#define MIN_UDP_SIZE 576
#define OBJ_MESSAGE_SIZE 108	// setMessage + seqMessage size
#define CUR_MESSAGE_SIZE 88

namespace TUIO {
	/**
	 * <p>The TuioServer25D class is the central TUIO protocol encoder component.
	 * In order to encode and send TUIO messages an instance of TuioServer25D needs to be created. The TuioServer25D instance then generates TUIO messaged
	 * which are sent via OSC over UDP to the configured IP address and port.</p> 
	 * <p>During runtime the each frame is marked with the initFrame and commitFrame methods, 
	 * while the currently present TuioObject25Ds are managed by the server with ADD, UPDATE and REMOVE methods in analogy to the TuioClient25D's TuioListener25D interface.</p> 
	 * <p><code>
	 * TuioClient25D *server = new TuioServer25D();<br/>
	 * ...<br/>
	 * server->initFrame(TuioTime::getSessionTime());<br/>
	 * TuioObject25D *tobj = server->addTuioObject(xpos,ypos, angle);<br/>
	 * TuioCursor25D *tcur = server->addTuioObject(xpos,ypos);<br/>
	 * server->commitFrame();<br/>
	 * ...<br/>
	 * server->initFrame(TuioTime::getSessionTime());<br/>
	 * server->updateTuioObject(tobj, xpos,ypos, angle);<br/>
	 * server->updateTuioCursor(tcur, xpos,ypos);<br/>
	 * server->commitFrame();<br/>
	 * ...<br/>
	 * server->initFrame(TuioTime::getSessionTime());<br/>
	 * server->removeTuioObject(tobj);<br/>
	 * server->removeTuioCursor(tcur);<br/>
	 * server->commitFrame();<br/>
	 * </code></p>
	 *
	 * Modification of TuioServer.h
	 * @author Olaf Schulz
	 * @version 1.4
	 */ 
	class TuioServer25D { 
		
	public:

		/**
		 * The default constructor creates a TuioServer25D that sends to the default TUIO port 3333 on localhost
		 * using the maximum packet size of 65536 bytes to use single packets on the loopback device
		 */
		TuioServer25D();

		/**
		 * This constructor creates a TuioServer25D that sends to the provided port on the the given host
		 * using a default packet size of 1492 bytes to deliver unfragmented UDP packets on a LAN
		 *
		 * @param  host  the receiving host name
		 * @param  port  the outgoing TUIO UDP port number
		 */
		TuioServer25D(const char *host, int port);

		/**
		 * This constructor creates a TuioServer25D that sends to the provided port on the the given host
		 * the packet UDP size can be set to a value between 576 and 65536 bytes
		 *
		 * @param  host  the receiving host name
		 * @param  port  the outgoing TUIO UDP port number
		 * @param  size  the maximum UDP packet size
		 */
		TuioServer25D(const char *host, int port, int size);

		/**
		 * The destructor is doing nothing in particular. 
		 */
		~TuioServer25D();
		
		/**
		 * Creates a new TuioObject25D based on the given arguments.
		 * The new TuioObject25D is added to the TuioServer25D's internal list of active TuioObject25Ds 
		 * and a reference is returned to the caller.
		 *
		 * @param	sym	the Symbol ID  to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle to assign
		 * @return	reference to the created TuioObject25D
		 */
		TuioObject25D* addTuioObject(int sym, float xp, float yp, float zp, float a);

		/**
		 * Updates the referenced TuioObject25D based on the given arguments.
		 *
		 * @param	tobj	the TuioObject25D to update
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle to assign
		 */
		void updateTuioObject(TuioObject25D *tobj, float xp, float yp, float zp, float a);

		/**
		 * Removes the referenced TuioObject25D from the TuioServer25D's internal list of TuioObject25Ds
		 * and deletes the referenced TuioObject25D afterwards
		 *
		 * @param	tobj	the TuioObject25D to remove
		 */
		void removeTuioObject(TuioObject25D *tobj);

		/**
		 * Adds an externally managed TuioObject25D to the TuioServer25D's internal list of active TuioObject25Ds 
		 *
		 * @param	tobj	the TuioObject25D to add
		 */
		void addExternalTuioObject25D(TuioObject25D *tobj);

		/**
		 * Updates an externally managed TuioObject25D 
		 *
		 * @param	tobj	the TuioObject25D to update
		 */
		void updateExternalTuioObject25D(TuioObject25D *tobj);

		/**
		 * Removes an externally managed TuioObject25D from the TuioServer25D's internal list of TuioObject25Ds
		 * The referenced TuioObject25D is not deleted
		 *
		 * @param	tobj	the TuioObject25D to remove
		 */
		void removeExternalTuioObject25D(TuioObject25D *tobj);
		
		/**
		 * Creates a new TuioCursor25D based on the given arguments.
		 * The new TuioCursor25D is added to the TuioServer25D's internal list of active TuioCursor25Ds 
		 * and a reference is returned to the caller.
		 *
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @return	reference to the created TuioCursor25D
		 */
		TuioCursor25D* addTuioCursor(float xp, float yp, float zp);
		TuioCursor25D* addTuioCursor(float xp, float yp, float zp, long _sessionID);

		/**
		 * Updates the referenced TuioCursor25D based on the given arguments.
		 *
		 * @param	tcur	the TuioObject25D to update
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 */
		void updateTuioCursor(TuioCursor25D *tcur, float xp, float yp, float zp);

		/**
		 * Removes the referenced TuioCursor25D from the TuioServer25D's internal list of TuioCursor25Ds
		 * and deletes the referenced TuioCursor25D afterwards
		 *
		 * @param	tcur	the TuioCursor25D to remove
		 */
		void removeTuioCursor(TuioCursor25D *tcur);

		/**
		 * Updates an externally managed TuioCursor25D 
		 *
		 * @param	tcur	the TuioCursor25D to update
		 */
		void addExternalTuioCursor25D(TuioCursor25D *tcur);

		/**
		 * Updates an externally managed TuioCursor25D 
		 *
		 * @param	tcur	the TuioCursor25D to update
		 */
		void updateExternalTuioCursor25D(TuioCursor25D *tcur);

		/**
		 * Removes an externally managed TuioCursor25D from the TuioServer25D's internal list of TuioCursor25D
		 * The referenced TuioCursor25D is not deleted
		 *
		 * @param	tcur	the TuioCursor25D to remove
		 */
		void removeExternalTuioCursor25D(TuioCursor25D *tcur);
		
		/**
		 * Initializes a new frame with the given TuioTime
		 *
		 * @param	ttime	the frame time
		 */
		void initFrame(TuioTime ttime);
		
		/**
		 * Commits the current frame.
		 * Generates and sends TUIO messages of all currently active and updated TuioObject25Ds and TuioCursor25Ds.
		 */
		void commitFrame();

		/**
		 * Returns the next available Session ID for external use.
		 * @return	the next available Session ID for external use
		 */
		long getSessionID();

		/**
		 * Returns the current frame ID for external use.
		 * @return	the current frame ID for external use
		 */
		long getFrameID();
		
		/**
		 * Returns the current frame ID for external use.
		 * @return	the current frame ID for external use
		 */
		TuioTime getFrameTime();

		/**
		 * Generates and sends TUIO messages of all currently active TuioObject25Ds and TuioCursor25Ds.
		 */
		void sendFullMessages();		

		/**
		 * Disables the periodic full update of all currently active TuioObject25Ds and TuioCursor25Ds 
		 *
		 * @param	interval	update interval in seconds, defaults to one second
		 */
		void enablePeriodicMessages(int interval=1);

		/**
		 * Disables the periodic full update of all currently active and inactive TuioObject25Ds and TuioCursor25Ds 
		 */
		void disablePeriodicMessages();

		/**
		 * Enables the full update of all currently active and inactive TuioObject25Ds and TuioCursor25Ds 
		 *
		 */
		void enableFullUpdate()  {
			full_update = true;
		}
		
		/**
		 * Disables the full update of all currently active and inactive TuioObject25Ds and TuioCursor25Ds 
		 */
		void disableFullUpdate() {
			full_update = false;
		}
		
		/**
		 * Returns true if the periodic full update of all currently active TuioObject25Ds and TuioCursor25Ds is enabled.
		 * @return	true if the periodic full update of all currently active TuioObject25Ds and TuioCursor25Ds is enabled
		 */
		bool periodicMessagesEnabled() {
			return periodic_update;
		}
	
		/**
		 * Returns the periodic update interval in seconds.
		 * @return	the periodic update interval in seconds
		 */
		int getUpdateInterval() {
			return update_interval;
		}
		
		/**
		 * Returns a List of all currently inactive TuioObject25Ds
		 *
		 * @return  a List of all currently inactive TuioObject25Ds
		 */
		std::list<TuioObject25D*> getUntouchedObjects();

		/**
		 * Returns a List of all currently inactive TuioCursor25Ds
		 *
		 * @return  a List of all currently inactive TuioCursor25Ds
		 */
		std::list<TuioCursor25D*> getUntouchedCursors();
		
		/**
		 * Calculates speed and acceleration values for all currently inactive TuioObject25Ds
		 */
		void stopUntouchedMovingObjects();

		/**
		 * Calculates speed and acceleration values for all currently inactive TuioCursor25Ds
		 */
		void stopUntouchedMovingCursors();
		
		/**
		 * Removes all currently inactive TuioObject25Ds from the TuioServer25D's internal list of TuioObject25Ds
		 */
		void removeUntouchedStoppedObjects();

		/**
		 * Removes all currently inactive TuioCursor25Ds from the TuioServer25D's internal list of TuioCursor25Ds
		 */
		void removeUntouchedStoppedCursors();

		/**
		 * Returns a List of all currently active TuioObject25Ds
		 *
		 * @return  a List of all currently active TuioObject25Ds
		 */
		std::list<TuioObject25D*> getTuioObject25Ds();
		
		
		/**
		 * Returns a List of all currently active TuioCursor25Ds
		 *
		 * @return  a List of all currently active TuioCursor25Ds
		 */
		std::list<TuioCursor25D*> getTuioCursor25Ds();
		
		/**
		 * Returns the TuioObject25D corresponding to the provided Session ID
		 * or NULL if the Session ID does not refer to an active TuioObject25D
		 *
		 * @return  an active TuioObject25D corresponding to the provided Session ID or NULL
		 */
		TuioObject25D* getTuioObject25D(long s_id);
		
		/**
		 * Returns the TuioCursor25D corresponding to the provided Session ID
		 * or NULL if the Session ID does not refer to an active TuioCursor25D
		 *
		 * @return  an active TuioCursor25D corresponding to the provided Session ID or NULL
		 */
		TuioCursor25D* getTuioCursor25D(long s_id);

		/**
		 * Returns the TuioObject25D closest to the provided coordinates
		 * or NULL if there isn't any active TuioObject25D
		 *
		 * @return  the closest TuioObject25D to the provided coordinates or NULL
		 */
		TuioObject25D* getClosestTuioObject25D(float xp, float yp, float zp);
		
		/**
		 * Returns the TuioCursor25D closest to the provided coordinates
		 * or NULL if there isn't any active TuioCursor25D
		 *
		 * @return  the closest TuioCursor25D corresponding to the provided coordinates or NULL
		 */
		TuioCursor25D* getClosestTuioCursor25D(float xp, float yp, float zp);
		
		/**
		 * Returns true if this TuioServer25D is currently connected.
		 * @return	true if this TuioServer25D is currently connected
		 */
		bool isConnected() { return connected; }
		
		/**
		 * The TuioServer25D prints verbose TUIO event messages to the console if set to true.
		 * @param	verbose	verbose message output if set to true
		 */
		void setVerbose(bool verbose) { this->verbose=verbose; }
		
	private:
		std::list<TuioObject25D*> objectList;
		std::list<TuioCursor25D*> cursorList;
		
		int maxCursorID;
		std::list<TuioCursor25D*> freeCursorList;
		std::list<TuioCursor25D*> freeCursorBuffer;
		
		UdpTransmitSocket *socket;	
		osc::OutboundPacketStream  *oscPacket;
		char *oscBuffer; 
		osc::OutboundPacketStream  *fullPacket;
		char *fullBuffer; 
		
		void initialize(const char *host, int port, int size);

		void sendEmptyCursorBundle();
		void startCursorBundle();
		void addCursorMessage(TuioCursor25D *tcur);
		void sendCursorBundle(long fseq);
		
		void sendEmptyObjectBundle();
		void startObjectBundle();
		void addObjectMessage(TuioObject25D *tobj);
		void sendObjectBundle(long fseq);
		
		bool full_update;
		int update_interval;
		bool periodic_update;

		long currentFrame;
		TuioTime currentFrameTime;
		bool updateObject, updateCursor;
		long lastCursorUpdate, lastObjectUpdate;

		long sessionID;
		bool verbose;

#ifndef WIN32
		pthread_t thread;
#else
		HANDLE thread;
#endif	
		bool connected;
	};
};
#endif /* INCLUDED_TuioServer25D25D_H */
