/*
 *  RingAnimationObject.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "RingAnimationObject.h"

float fri_ction = 0.7;
float sp_ring = 0.81;

RingAnimationObject::RingAnimationObject(){
	x = 0;
	y = 0;
	
	px=py=0;
	scaleVal = 1;
	scaleV = 0;
	recordedScaleVal = 1;
}

void RingAnimationObject::setRingURLList(std::vector<string> urlList){
	body.setURLList(urlList);
}

void RingAnimationObject::setup(float svx, float svy){
	vx = vy = 0;
	vTargetX = svx;
	vTargetY = svy;
	vBaseX = svx;
	vBaseY = svy;
}
void RingAnimationObject::update() {
	targetScaleVal += 0.1*(1-targetScaleVal);
	scaleVal += 0.1*(targetScaleVal - scaleVal);
	vx += 0.4*(vTargetX - vx);
	vy += 0.4*(vTargetY - vy);
	x += vx;
	y += vy;
	
	if(x<0)x=800;
	if(x>800)x=0;
	if(y<0)y=600;
	if(y>600)y=0;
}
void RingAnimationObject::draw() {
	angle = 360*(x/800)*PI/180;
	ofPushMatrix();
	ofTranslate(x, y, 0);
		body.draw(0, 0);
	ofPopMatrix();
	x--;
	if(x<0)x=800;
}

void RingAnimationObject::multipleSpeed(float Num){
	vTargetX = vBaseX*Num;
	vTargetY = vBaseY*Num;
}


void RingAnimationObject::applyScale(float sc){
	targetScaleVal = sc;
}
