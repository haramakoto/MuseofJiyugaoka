/*
 *  RingAnimationObject.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RINGANIMATION_H__
#define __RINGANIMATION_H__


#include "ofMain.h"
#include "Animator.h"

class RingAnimationObject{
public:
	RingAnimationObject();
	
	Animator body;
	float yOffset;
	float angle;
	
	float vx, vy;
	float vTargetX;
	float vTargetY;
	float vBaseX;
	float vBaseY;
	
	void setRingURLList(std::vector<string> urlList);
	void update();
	void draw();
	void setup(float svx, float svy);
	void applyScale(float sc);
	void multipleSpeed(float Num);
	float x;
	float y;
	float px;
	float py;
	float scaleVal;
	float recordedScaleVal;
	float scaleV;
	float targetScaleVal;
};

#endif __RINGANIMATION_H__
