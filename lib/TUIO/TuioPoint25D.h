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

#ifndef INCLUDED_TUIOPOINT25D_H
#define INCLUDED_TUIOPOINT25D_H
#include "TuioTime.h"
#include <iostream>

#ifndef M_PI
#define M_PI	3.14159265358979323846

#endif

namespace TUIO {
	
	/**
	 * The TuioPoint25D class on the one hand is a simple container and utility class to handle TUIO positions in general, 
	 * on the other hand the TuioPoint25D is the base class for the TuioCursor and TuioObject classes.
	 *
	 * Modification of TuioPoint.h
	 * @author Olaf Schulz
	 * @version 1.4
	 */ 
	class TuioPoint25D {
		
	protected:
		/**
		 * X,Y and Z coordinates, representated as a floating point value in a range of 0..1  
		 */
		float xpos;
		float ypos;
		float zpos;
		/**
		 * The time stamp of the last update represented as TuioTime (time since session start)
		 */
		TuioTime currentTime;
		/**
		 * The creation time of this TuioPoint25D represented as TuioTime (time since session start)
		 */
		TuioTime startTime;
		
	public:
		/**
		 * The default constructor takes no arguments and sets   
		 * its coordinate attributes to zero and its time stamp to the current session time.
		 */
		TuioPoint25D (float xp, float yp, float zp) {
			xpos = xp;
			ypos = yp;
			zpos = zp;
			currentTime = TuioTime::getSessionTime();
			startTime = currentTime;
		};
	
		/**
		 * This constructor takes a TuioTime object and two floating point coordinate arguments and sets   
		 * its coordinate attributes to these values and its time stamp to the provided TUIO time object.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 */
		TuioPoint25D (TuioTime ttime, float xp, float yp, float zp) {
			xpos = xp;
			ypos = yp;
			zpos = zp;
			currentTime = ttime;
			startTime = currentTime;
		};
		
		/**
		 * This constructor takes a TuioPoint25D argument and sets its coordinate attributes 
		 * to the coordinates of the provided TuioPoint25D and its time stamp to the current session time.
		 *
		 * @param	tpoint	the TuioPoint25D to assign
		 */
		TuioPoint25D (TuioPoint25D *tpoint) {
			xpos = tpoint->getX();
			ypos = tpoint->getY();
			zpos = tpoint->getZ();
			currentTime = TuioTime::getSessionTime();
			startTime = currentTime;
		};
		
		/**
		 * The destructor is doing nothing in particular. 
		 */
		~TuioPoint25D(){};
		
		/**
		 * Takes a TuioPoint25D argument and updates its coordinate attributes 
		 * to the coordinates of the provided TuioPoint25D and leaves its time stamp unchanged.
		 *
		 * @param	tpoint	the TuioPoint25D to assign
		 */
		void update (TuioPoint25D *tpoint) {
			xpos = tpoint->getX();
			ypos = tpoint->getY();
			zpos = tpoint->getZ();
		};
		
		/**
		 * Takes two floating point coordinate arguments and updates its coordinate attributes 
		 * to the coordinates of the provided TuioPoint25D and leaves its time stamp unchanged.
		 *
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 */		
		void update (float xp, float yp, float zp) {
			xpos = xp;
			ypos = yp;
			zpos = zp;
		};		
		
		/**
		 * Takes a TuioTime object and two floating point coordinate arguments and updates its coordinate attributes 
		 * to the coordinates of the provided TuioPoint25D and its time stamp to the provided TUIO time object.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 */
		void update (TuioTime ttime, float xp, float yp, float zp) {
			xpos = xp;
			ypos = yp;
			zpos = zp;
			currentTime = ttime;
		};

		
		/**
		 * Returns the X coordinate of this TuioPoint25D. 
		 * @return	the X coordinate of this TuioPoint25D
		 */
		float getX() { 
			return xpos;
		};
		
		/**
		 * Returns the Y coordinate of this TuioPoint25D. 
		 * @return	the Y coordinate of this TuioPoint25D
		 */
		float getY() {
			return ypos;
		};
		
		/**
		 * Returns the Z coordinate of this TuioPoint25D. 
		 * @return	the Z coordinate of this TuioPoint25D
		 */
		float getZ() {
			return zpos;
		};
		
		/**
		 * Returns the distance to the provided coordinates 
		 *
		 * @param	xp	the X coordinate of the distant point
		 * @param	yp	the Y coordinate of the distant point
		 * @param	zp	the Z coordinate of the distant point
		 * @return	the distance to the provided coordinates
		 */
		float getDistance(float xp, float yp, float zp) {
			float dx = xpos-xp;
			float dy = ypos-yp;
			float dz = zpos-zp;
			return sqrtf(dx*dx+dy*dy+dz*dz);
		}
		
		/**
		 * Returns the distance to the provided TuioPoint25D 
		 *
		 * @param	tpoint	the distant TuioPoint25D
		 * @return	the distance to the provided TuioPoint25D
		 */
		float getDistance(TuioPoint25D *tpoint) {
			return getDistance(tpoint->getX(),tpoint->getY(),tpoint->getZ());
		}
		
		/**
		 * Returns the angle to the provided coordinates 
		 *
		 * @param	xp	the X coordinate of the distant point
		 * @param	yp	the Y coordinate of the distant point
		 * @return	the angle to the provided coordinates
		 */
		 float getAngle(float xp, float yp) {
			float side = xpos-xp;
			float height = ypos-yp;
			float distance = getDistance(xp,yp,0);
			
			float angle = (float)(asin(side/distance)+M_PI/2);
			if (height<0) angle = 2.0f*(float)M_PI-angle;
			
			return angle;
		}
		
		/**
		 * Returns the angle to the provided TuioPoint25D 
		 *
		 * @param	tpoint	the distant TuioPoint25D
		 * @return	the angle to the provided TuioPoint25D
		 */
		float getAngle(TuioPoint25D *tpoint) {
			return getAngle(tpoint->getX(),tpoint->getY());
		}

		/**
		 * Returns the angle in degrees to the provided coordinates 
		 *
		 * @param	xp	the X coordinate of the distant point
		 * @param	yp	the Y coordinate of the distant point
		 * @return	the angle in degrees to the provided TuioPoint25D
		 */
		float getAngleDegrees(float xp, float yp) {
			return ((getAngle(xp,yp)/(float)M_PI)*180.0f);
		}

		/**
		 * Returns the angle in degrees to the provided TuioPoint25D 
		 *
		 * @param	tpoint	the distant TuioPoint25D
		 * @return	the angle in degrees to the provided TuioPoint25D
		 */
		float getAngleDegrees(TuioPoint25D *tpoint) {
			return ((getAngle(tpoint)/(float)M_PI)*180.0f);
		}
		
		/**
		 * Returns the X coordinate in pixels relative to the provided screen width. 
		 *
		 * @param	width	the screen width
		 * @return	the X coordinate of this TuioPoint25D in pixels relative to the provided screen width
		 */
		int getScreenX(int width) { 
			return (int)floor(xpos*width+0.5f);
		};
		
		/**
		 * Returns the Y coordinate in pixels relative to the provided screen height. 
		 *
		 * @param	height	the screen height
		 * @return	the Y coordinate of this TuioPoint25D in pixels relative to the provided screen height
		 */
		int getScreenY(int height) {
			return (int)floor(ypos*height+0.5f);
		};
		
		/**
		 * Returns current time stamp of this TuioPoint25D as TuioTime 
		 *
		 * @return	the  time stamp of this TuioPoint25D as TuioTime
		 */
		TuioTime getTuioTime() { 
			return currentTime;
		};
		
		/**
		 * Returns the start time of this TuioPoint25D as TuioTime. 
		 *
		 * @return	the start time of this TuioPoint25D as TuioTime
		 */
		TuioTime getStartTime() {
			return startTime;
		};
	};
};
#endif
