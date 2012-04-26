/*
 TUIO C++ Library - part of the reacTIVision project
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

#ifndef INCLUDED_TUIOCLIENT25D_H
#define INCLUDED_TUIOCLIENT25D_H

#ifndef WIN32
#include <pthread.h>
#include <sys/time.h>
#else
#include <windows.h>
#endif

#include <iostream>
#include <list>
#include <algorithm>
#include <cstring>

#include "osc/OscReceivedElements.h"
#include "osc/OscPrintReceivedElements.h"

#include "ip/UdpSocket.h"
#include "ip/PacketListener.h"

#include "TuioListener25D.h"
#include "TuioObject25D.h"
#include "TuioCursor25D.h"

namespace TUIO {
	
	/**
	 * <p>The TuioClient25D class is the central TUIO protocol decoder component. It provides a simple callback infrastructure using the {@link TuioListener25D} interface.
	 * In order to receive and decode TUIO messages an instance of TuioClient25D needs to be created. The TuioClient25D instance then generates TUIO events
	 * which are broadcasted to all registered classes that implement the {@link TuioListener25D} interface.</p> 
	 * <p><code>
	 * TuioClient25D *client = new TuioClient25D();<br/>
	 * client->addTuioListener(myTuioListener25D);<br/>
	 * client->connect();<br/>
	 * </code></p>
	 *
	 * Modification of TuioClient.h
	 * @author Olaf Schulz
	 * @version 1.4
	 */ 
	class TuioClient25D : public PacketListener { 
		
	public:
		/**
		 * This constructor creates a TuioClient25D that listens to the provided port
		 *
		 * @param  port  the incoming TUIO UDP port number, defaults to 3333 if no argument is provided
		 */
		TuioClient25D(int port=3333);

		/**
		 * The destructor is doing nothing in particular. 
		 */
		~TuioClient25D();
		
		/**
		 * The TuioClient25D starts listening to TUIO messages on the configured UDP port
		 * All received TUIO messages are decoded and the resulting TUIO events are broadcasted to all registered TuioListener25Ds
		 *
		 * @param  lock  running in the background if set to false (default)
		 */
		void connect(bool lock=false);

		/**
		 * The TuioClient25D stops listening to TUIO messages on the configured UDP port
		 */
		void disconnect();

		/**
		 * Returns true if this TuioClient25D is currently connected.
		 * @return	true if this TuioClient25D is currently connected
		 */
		bool isConnected() { return connected; }
				
		/**
		 * Adds the provided TuioListener25D to the list of registered TUIO event listeners
		 *
		 * @param  listener  the TuioListener25D to add
		 */
		void addTuioListener(TuioListener25D *listener);

		/**
		 * Removes the provided TuioListener25D from the list of registered TUIO event listeners
		 *
		 * @param  listener  the TuioListener25D to remove
		 */
		void removeTuioListener25D(TuioListener25D *listener);

		/**
		 * Removes all TuioListener25D from the list of registered TUIO event listeners
		 */
		void removeAllTuioListener25Ds() {	
			listenerList.clear();
		}

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
		 * Locks the TuioObject25D list in order to avoid updates during access
		 */
		void lockObjectList();

		/**
		 * Releases the lock of the TuioObject25D list
		 */
		void unlockObjectList();

		/**
		 * Locks the TuioCursor25D list in order to avoid updates during access
		 */
		void lockCursorList();

		/**
		 * Releases the lock of the TuioCursor25D list
		 */
		void unlockCursorList();

		void ProcessPacket( const char *data, int size, const IpEndpointName &remoteEndpoint );
		UdpListeningReceiveSocket *socket;
				
	protected:
		void ProcessBundle( const osc::ReceivedBundle& b, const IpEndpointName& remoteEndpoint);
		
		/**
		 * The OSC callback method where all TUIO messages are received and decoded
		 * and where the TUIO event callbacks are dispatched
		 *
		 * @param  message		the received OSC message
		 * @param  remoteEndpoint	the received OSC message origin
		 */
		void ProcessMessage( const osc::ReceivedMessage& message, const IpEndpointName& remoteEndpoint);
		
	private:
		std::list<TuioListener25D*> listenerList;
		
		std::list<TuioObject25D*> objectList, frameObjects;
		std::list<long> aliveObjectList;
		std::list<TuioCursor25D*> cursorList, frameCursors;
		std::list<long> aliveCursorList;
		
		osc::int32 currentFrame;
		TuioTime currentTime;
			
		std::list<TuioCursor25D*> freeCursorList, freeCursorBuffer;
		int maxCursorID;
		
#ifndef WIN32
		pthread_t thread;
		pthread_mutex_t objectMutex;
		pthread_mutex_t cursorMutex;
		//pthread_mutexattr_t attr_p;
#else
		HANDLE thread;
		HANDLE objectMutex;
		HANDLE cursorMutex;
#endif	
				
		bool locked;
		bool connected;
	};
};
#endif /* INCLUDED_TUIOCLIENT25D_H */
