/*
 *  RingAnimationPos.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/12/02.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RINGANIMATIONPOS_H__
#define __RINGANIMATIONPOS_H__


#include "ofMain.h"

class RingAnimationPos{
public:
	RingAnimationPos();
	
	float x,y,vx,vy, r;
	float vTargetX;
	float vTargetY;
	float vBaseX;
	float vBaseY;
	float scaleVal;
	float recordedScaleVal;
	float scaleV;
	
	void update();
	void draw();
	void setup(float svx, float svy);
	void applyScale(float sc);
	void multipleSpeed(float Num);
	
};

#endif __RINGANIMATIONPOS_H__