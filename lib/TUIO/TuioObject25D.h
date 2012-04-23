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

#ifndef INCLUDED_TUIOOBJECT_H
#define INCLUDED_TUIOOBJECT_H

#include <math.h>
#include "TuioContainer25D.h"

#define TUIO_ROTATING 5

namespace TUIO {
	
	/**
	 * The TuioObject25D class encapsulates /tuio/25Dobj TUIO objects.
	 *
	 * Modification of TuioObject.h
	 * @author Olaf Schulz
	 * @version 1.4
	 */ 
	class TuioObject25D: public TuioContainer25D {
		
	protected:
		/**
		 * The individual symbol ID number that is assigned to each TuioObject25D.
		 */ 
		int symbol_id;
		/**
		 * The rotation angle value.
		 */ 
		float angle;
		/**
		 * The rotation speed value.
		 */ 
		float rotation_speed;
		/**
		 * The rotation acceleration value.
		 */ 
		float rotation_accel;
		
	public:
		/**
		 * This constructor takes a TuioTime argument and assigns it along with the provided 
		 * Session ID, Symbol ID, X and Y coordinate and angle to the newly created TuioObject25D.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	si	the Session ID  to assign
		 * @param	sym	the Symbol ID  to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle to assign
		 */
		TuioObject25D (TuioTime ttime, long si, int sym, float xp, float yp, float zp, float a):TuioContainer25D(ttime, si, xp, yp, zp) {
			symbol_id = sym;
			angle = a;
			rotation_speed = 0.0f;
			rotation_accel = 0.0f;
		};

		/**
		 * This constructor takes the provided Session ID, Symbol ID, X and Y coordinate 
		 * and angle, and assigs these values to the newly created TuioObject25D.
		 *
		 * @param	si	the Session ID  to assign
		 * @param	sym	the Symbol ID  to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle to assign
		 */	
		TuioObject25D (long si, int sym, float xp, float yp, float zp, float a):TuioContainer25D(si, xp, yp, zp) {
			symbol_id = sym;
			angle = a;
			rotation_speed = 0.0f;
			rotation_accel = 0.0f;
		};
		
		/**
		 * This constructor takes the atttibutes of the provided TuioObject25D 
		 * and assigs these values to the newly created TuioObject25D.
		 *
		 * @param	tobj	the TuioObject25D to assign
		 */
		TuioObject25D (TuioObject25D *tobj):TuioContainer25D(tobj) {
			symbol_id = tobj->getSymbolID();
			angle = tobj->getAngle();
			rotation_speed = 0.0f;
			rotation_accel = 0.0f;
		};
		
		/**
		 * The destructor is doing nothing in particular. 
		 */
		~TuioObject25D() {};
		
		/**
		 * Takes a TuioTime argument and assigns it along with the provided 
		 * X and Y coordinate, angle, X and Y velocity, motion acceleration,
		 * rotation speed and rotation acceleration to the private TuioObject25D attributes.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle coordinate to assign
		 * @param	xs	the X velocity to assign
		 * @param	ys	the Y velocity to assign
		 * @param	zs	the Z velocitz to assign
		 * @param	rs	the rotation velocity to assign
		 * @param	ma	the motion acceleration to assign
		 * @param	ra	the rotation acceleration to assign
		 */
		void update (TuioTime ttime, float xp, float yp, float zp, float a, float xs, float ys, float zs, float rs, float ma, float ra) {
			TuioContainer25D::update(ttime,xp,yp,zp,xs,ys,zs,ma);
			angle = a;
			rotation_speed = rs;
			rotation_accel = ra;
			if ((rotation_accel!=0) && (state==TUIO_STOPPED)) state = TUIO_ROTATING;
		};

		/**
		 * Assigns the provided X and Y coordinate, angle, X and Y velocity, motion acceleration
		 * rotation velocity and rotation acceleration to the private TuioContainer25D attributes.
		 * The TuioTime time stamp remains unchanged.
		 *
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	zp	the Z coordinate to assign
		 * @param	a	the angle coordinate to assign
		 * @param	xs	the X velocity to assign
		 * @param	ys	the Y velocity to assign
		 * @param	zs	the Z velocitz to assign
		 * @param	rs	the rotation velocity to assign
		 * @param	ma	the motion acceleration to assign
		 * @param	ra	the rotation acceleration to assign
		 */
		void update (float xp, float yp, float zp, float a, float xs, float ys, float zs, float rs, float ma, float ra) {
			TuioContainer25D::update(xp,yp,zp,xs,ys,zs,ma);
			angle = a;
			rotation_speed = rs;
			rotation_accel = ra;
			if ((rotation_accel!=0) && (state==TUIO_STOPPED)) state = TUIO_ROTATING;
		};
		
		/**
		 * Takes a TuioTime argument and assigns it along with the provided 
		 * X and Y coordinate and angle to the private TuioObject25D attributes.
		 * The speed and accleration values are calculated accordingly.
		 *
		 * @param	ttime	the TuioTime to assign
		 * @param	xp	the X coordinate to assign
		 * @param	yp	the Y coordinate to assign
		 * @param	a	the angle coordinate to assign
		 */
		void update (TuioTime ttime, float xp, float yp, float zp, float a) {
			TuioPoint25D lastPoint = path.back();
			TuioContainer25D::update(ttime,xp,yp,zp);
			
			TuioTime diffTime = currentTime - lastPoint.getTuioTime();
			float dt = diffTime.getTotalMilliseconds()/1000.0f;
			float last_angle = angle;
			float last_rotation_speed = rotation_speed;
			angle = a;
			
			double da = (angle-last_angle)/(2*M_PI);
			if (da>M_PI*1.5) da-=(2*M_PI);
			else if (da<M_PI*1.5) da+=(2*M_PI);
			
			rotation_speed = (float)da/dt;
			rotation_accel =  (rotation_speed - last_rotation_speed)/dt;
			
			if ((rotation_accel!=0) && (state==TUIO_STOPPED)) state = TUIO_ROTATING;
		};

		/**
		 * This method is used to calculate the speed and acceleration values of a
		 * TuioObject25D with unchanged position and angle.
		 */
		void stop (TuioTime ttime) {
			update(ttime,xpos,ypos,zpos,angle);
		};
		
		/**
		 * Takes the atttibutes of the provided TuioObject25D 
		 * and assigs these values to this TuioObject25D.
		 * The TuioTime time stamp of this TuioContainer25D remains unchanged.
		 *
		 * @param	tobj	the TuioContainer25D to assign
		 */	
		void update (TuioObject25D *tobj) {
			TuioContainer25D::update(tobj);
			angle = tobj->getAngle();
			rotation_speed = tobj->getRotationSpeed();
			rotation_accel = tobj->getRotationAccel();
			if ((rotation_accel!=0) && (state==TUIO_STOPPED)) state = TUIO_ROTATING;
		};
		
		/**
		 * Returns the symbol ID of this TuioObject25D.
		 * @return	the symbol ID of this TuioObject25D
		 */
		int getSymbolID() { 
			return symbol_id;
		};
		
		/**
		 * Returns the rotation angle of this TuioObject25D.
		 * @return	the rotation angle of this TuioObject25D
		 */
		float getAngle() {
			return angle;
		};
		
		/**
		 * Returns the rotation angle in degrees of this TuioObject25D.
		 * @return	the rotation angle in degrees of this TuioObject25D
		 */
		float getAngleDegrees() { 
			return (float)(angle/M_PI*180);
		};
		
		/**
		 * Returns the rotation speed of this TuioObject25D.
		 * @return	the rotation speed of this TuioObject25D
		 */
		float getRotationSpeed() { 
			return rotation_speed;
		};
		
		/**
		 * Returns the rotation acceleration of this TuioObject25D.
		 * @return	the rotation acceleration of this TuioObject25D
		 */
		float getRotationAccel() {
			return rotation_accel;
		};

		/**
		 * Returns true of this TuioObject25D is moving.
		 * @return	true of this TuioObject25D is moving
		 */
		virtual bool isMoving() { 
			if ((state==TUIO_ACCELERATING) || (state==TUIO_DECELERATING) || (state==TUIO_ROTATING)) return true;
			else return false;
		};
	};
};
#endif
