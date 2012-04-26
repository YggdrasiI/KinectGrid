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

#ifndef INCLUDED_TUIOCONTAINER25D_H
#define INCLUDED_TUIOCONTAINER25D_H

#include <list>
#include <math.h>
#include "TuioPoint25D.h"
#include <iostream>

#define TUIO_ADDED 0
#define TUIO_ACCELERATING 1
#define TUIO_DECELERATING 2
#define TUIO_STOPPED 3
#define TUIO_REMOVED 4

namespace TUIO {
	
	/**
	 * The abstract TuioContainer25D class defines common attributes that apply to both subclasses {@link TuioObject} and {@link TuioCursor}.
	 *
	 * Modification of TuioContainer.h
	 * @author Olaf Schulz
	 * @version 1.4
	 */ 
	class TuioContainer25D: public TuioPoint25D {
		
	protected:
		/**
		 * The unique session ID number that is assigned to each TUIO object or cursor.
		 */ 
		long session_id;
		/**
		 * The X-axis velocity value.
		 */ 
		float x_speed;
		/**
		 * The Y-axis velocity value.
		 */ 
		float y_speed;
		/**
		 * The Z-axis velocity value.
		 */ 
		float z_speed;
		/**
		 * The motion speed value.
		 */ 
		float motion_speed;
		/**
		 * The motion acceleration value.
		 */ 
		float motion_accel;
		/**
		 * A List of TuioPoint25Ds containing all the previous positions of the TUIO component.
		 */ 
		std::list<TuioPoint25D> path;
		/**
		 * Reflects the current state of the TuioComponent
		 */ 
		int state;
		
	public:
		/**
		 * This constructor takes a TuioTime argument and assigns it along with the provided 
		 * Session ID, X, Y and Z coordinate to the newly created TuioContainer25D.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	si	the Session ID to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 */
		TuioContainer25D (TuioTime ttime, long si, float xp, float yp, float zp):TuioPoint25D(ttime, xp,yp,zp) {
			session_id = si;
			x_speed = 0.0f;
			y_speed = 0.0f;
			z_speed = 0.0f;
			motion_speed = 0.0f;
			motion_accel = 0.0f;			
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			state = TUIO_ADDED;
		};

		/**
		 * This constructor takes the provided Session ID, X and Y coordinate 
		 * and assigs these values to the newly created TuioContainer25D.
		 *
		 * @param	si	the Session ID to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 */
		TuioContainer25D (long si, float xp, float yp, float zp):TuioPoint25D(xp,yp,zp) {
			session_id = si;
			x_speed = 0.0f;
			y_speed = 0.0f;
			z_speed = 0.0f;
			motion_speed = 0.0f;
			motion_accel = 0.0f;			
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			state = TUIO_ADDED;
		};
		
		/**
		 * This constructor takes the atttibutes of the provided TuioContainer25D 
		 * and assigs these values to the newly created TuioContainer25D.
		 *
		 * @param	tcon	the TuioContainer25D to assign
		 */
		TuioContainer25D (TuioContainer25D *tcon):TuioPoint25D(tcon) {
			session_id = tcon->getSessionID();
			x_speed = 0.0f;
			y_speed = 0.0f;
			z_speed = 0.0f;
			motion_speed = 0.0f;
			motion_accel = 0.0f;
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			state = TUIO_ADDED;
		};
		
		/**
		 * The destructor is doing nothing in particular. 
		 */
		virtual ~TuioContainer25D(){};
		
		/**
		 * Takes a TuioTime argument and assigns it along with the provided 
		 * X and Y coordinate to the private TuioContainer25D attributes.
		 * The speed and accleration values are calculated accordingly.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 */
		virtual void update (TuioTime ttime, float xp, float yp, float zp) {
			TuioPoint25D lastPoint = path.back();
			TuioPoint25D::update(ttime,xp, yp,zp);
			
			TuioTime diffTime = currentTime - lastPoint.getTuioTime();
			float dt = diffTime.getTotalMilliseconds()/1000.0f;
			float dx = xpos - lastPoint.getX();
			float dy = ypos - lastPoint.getY();
			float dz = zpos - lastPoint.getZ();
			float dist = sqrt(dx*dx+dy*dy+dz*dz);
			float last_motion_speed = motion_speed;
			
			x_speed = dx/dt;
			y_speed = dy/dt;
			z_speed = dz/dt;
			motion_speed = dist/dt;
			motion_accel = (motion_speed - last_motion_speed)/dt;
			
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			if (motion_accel>0) state = TUIO_ACCELERATING;
			else if (motion_accel<0) state = TUIO_DECELERATING;
			else state = TUIO_STOPPED;
		};

		
		/**
		 * This method is used to calculate the speed and acceleration values of
		 * TuioContainer25Ds with unchanged positions.
		 */
		virtual void stop(TuioTime ttime) {
			update(ttime,xpos,ypos,zpos);
		};

		/**
		 * Takes a TuioTime argument and assigns it along with the provided 
		 * X and Y coordinate, X and Y velocity and acceleration
		 * to the private TuioContainer25D attributes.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	xs	the X velocity to assign
		 * @param	ys	the Y velocity to assign
		 * @param	zs	the Z velocitz to assign
		 * @param	ma	the acceleration to assign
		 */
		virtual void update (TuioTime ttime, float xp, float yp, float zp, float xs, float ys, float zs, float ma) {
			TuioPoint25D::update(ttime,xp, yp, zp);
			x_speed = xs;
			y_speed = ys;
			z_speed = zs;
			motion_speed = (float)sqrt(x_speed*x_speed+y_speed*y_speed+z_speed*z_speed);
			motion_accel = ma;
			
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			if (motion_accel>0) state = TUIO_ACCELERATING;
			else if (motion_accel<0) state = TUIO_DECELERATING;
			else state = TUIO_STOPPED;
		};
		
		/**
		 * Assigns the provided X and Y coordinate, X and Y velocity and acceleration
		 * to the private TuioContainer25D attributes. The TuioTime time stamp remains unchanged.
		 *
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	xs	the X velocity to assign
		 * @param	ys	the Y velocity to assign
		 * @param	zs	the Z velocitz to assign
		 * @param	ma	the acceleration to assign
		 */
		virtual void update (float xp, float yp, float zp, float xs, float ys, float zs, float ma) {
			TuioPoint25D::update(xp,yp,zp);
			x_speed = xs;
			y_speed = ys;
			z_speed = zs;
			motion_speed = (float)sqrt(x_speed*x_speed+y_speed*y_speed+z_speed*z_speed);
			motion_accel = ma;
			
			path.pop_back();
			TuioPoint25D p(currentTime,xpos,ypos,zpos);
			path.push_back(p);
			
			if (motion_accel>0) state = TUIO_ACCELERATING;
			else if (motion_accel<0) state = TUIO_DECELERATING;
			else state = TUIO_STOPPED;
		};
		
		/**
		 * Takes the atttibutes of the provided TuioContainer25D 
		 * and assigs these values to this TuioContainer25D.
		 * The TuioTime time stamp of this TuioContainer25D remains unchanged.
		 *
		 * @param	tcon	the TuioContainer25D to assign
		 */
		virtual void update (TuioContainer25D *tcon) {
			TuioPoint25D::update(tcon);
			x_speed = tcon->getXSpeed();
			y_speed =  tcon->getYSpeed();
			z_speed =  tcon->getZSpeed();
			motion_speed =  tcon->getMotionSpeed();
			motion_accel = tcon->getMotionAccel();
			
			TuioPoint25D p(tcon->getTuioTime(),xpos,ypos,zpos);
			path.push_back(p);
			
			if (motion_accel>0) state = TUIO_ACCELERATING;
			else if (motion_accel<0) state = TUIO_DECELERATING;
			else state = TUIO_STOPPED;
		};
		
		/**
		 * Assigns the REMOVE state to this TuioContainer25D and sets
		 * its TuioTime time stamp to the provided TuioTime argument.
		 *
		 * @param	ttime	the TuioTime to assign
		 */
		virtual void remove(TuioTime ttime) {
			currentTime = ttime;
			state = TUIO_REMOVED;
		}

		/**
		 * Returns the Session ID of this TuioContainer25D.
		 * @return	the Session ID of this TuioContainer25D
		 */
		virtual long getSessionID() { 
			return session_id;
		};
		
		/**
		 * Returns the X velocity of this TuioContainer25D.
		 * @return	the X velocity of this TuioContainer25D
		 */
		virtual float getXSpeed() { 
			return x_speed;
		};

		/**
		 * Returns the Y velocity of this TuioContainer25D.
		 * @return	the Y velocity of this TuioContainer25D
		 */
		virtual float getYSpeed() { 
			return y_speed;
		};
		
		/**
		 * Returns the Z velocity of this TuioContainer25D.
		 * @return	the Z velocity of this TuioContainer25D
		 */
		virtual float getZSpeed() { 
			return z_speed;
		};
		
		/**
		 * Returns the position of this TuioContainer25D.
		 * @return	the position of this TuioContainer25D
		 */
		virtual TuioPoint25D getPosition() {
			TuioPoint25D p(xpos,ypos,zpos);
			return p;
		};
		
		/**
		 * Returns the path of this TuioContainer25D.
		 * @return	the path of this TuioContainer25D
		 */
		virtual std::list<TuioPoint25D> getPath() {
			return path;
		};
		
		/**
		 * Returns the motion speed of this TuioContainer25D.
		 * @return	the motion speed of this TuioContainer25D
		 */
		virtual float getMotionSpeed() {
			return motion_speed;
		};
		
		/**
		 * Returns the motion acceleration of this TuioContainer25D.
		 * @return	the motion acceleration of this TuioContainer25D
		 */
		virtual float getMotionAccel() {
			return motion_accel;
		};
		
		/**
		 * Returns the TUIO state of this TuioContainer25D.
		 * @return	the TUIO state of this TuioContainer25D
		 */
		virtual int getTuioState() { 
			return state;
		};	
		
		/**
		 * Returns true of this TuioContainer25D is moving.
		 * @return	true of this TuioContainer25D is moving
		 */
		virtual bool isMoving() { 
			if ((state==TUIO_ACCELERATING) || (state==TUIO_DECELERATING)) return true;
			else return false;
		};
	};
};
#endif /* INCLUDED_TUIOCONTAINER25D_H */
