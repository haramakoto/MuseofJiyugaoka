/*
 *  RingAnimationPos.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/12/02.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "RingAnimationPos.h"

float friction = 0.7;
float spring = 0.81;

RingAnimationPos::RingAnimationPos(){
	x=0;
	y=0;
	vx=0;
	vy=0;
	vTargetX = -10;
	vTargetY = -10;
	vBaseX = -10;
	vBaseY = -10;
	scaleV = 0;
	r=0;
	scaleVal = recordedScaleVal = 1;
}

void RingAnimationPos::multipleSpeed(float Num){
	vTargetX = vBaseX*Num;
	vTargetY = vBaseY*Num;
}

void RingAnimationPos::setup(float svx, float svy) {
	vTargetX = svx;
	vTargetY = svy;
	vBaseX = svx;
	vBaseY = svy;
}
void RingAnimationPos::update() {
	vTargetX += 0.1*(vBaseX - vTargetX);
	vTargetY += 0.1*(vBaseY - vTargetY);
	vx += 0.4*(vTargetX - vx);
	vy += 0.4*(vTargetY - vy);
	x += vx;
	y += vy;
	r = atan2(vy, vx);
	if(x<0)x=800;
	if(x>800)x=0;
	if(y<0)y=600;
	if(y>600)y=0;
}

void RingAnimationPos::applyScale(float sc){
	scaleVal = sc;
	float scaledis = scaleVal - recordedScaleVal;
	float a = spring*scaledis;
	scaleV += a;
	scaleV *= friction;
	
	scaleVal = recordedScaleVal+scaleV;
}