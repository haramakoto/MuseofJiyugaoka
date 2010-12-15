/*
 *  Wing.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Wing.h"

int wingWidth=460;

Wing::Wing(){
	isEnd = false;
	
	LWingList.push_back("dummyWing.png");
	LWingList.push_back("wingl.png");
	LWingList.push_back("wingl.png");
	LWingList.push_back("wingl.png");
	LWingList.push_back("effelL.png");
	LWingList.push_back("wing5L.png");
	
	RWingList.push_back("dummyWing");
	RWingList.push_back("wing.png");
	RWingList.push_back("wing.png");
	RWingList.push_back("wing.png");
	RWingList.push_back("effelR.png");
	RWingList.push_back("wing5R.png");
	
}
void Wing::initWing(bool lr,int sceneIndex){
	L_R = lr;
	if(lr){
		WingBody.loadImage(RWingList[sceneIndex]);
	}else {
		WingBody.loadImage(LWingList[sceneIndex]);
	}
}

void Wing::setup() {
	
	scaleVal = 0;
	rotateVal = 0;

}
void Wing::update() {
	
}
void Wing::draw() {
	ofPushMatrix();
	if(L_R){
		ofTranslate(0, -80, 0);
		ofRotate(30*cos(rotateVal/TWO_PI), 0, 0, 1);
	}else {
		ofTranslate(800, -80, 0);
		ofRotate(-30*cos(rotateVal/TWO_PI), 0, 0, 1);
	}

	ofScale(scaleVal, scaleVal, 1);
		WingBody.draw(-wingWidth/2, 0);
	ofPopMatrix();
	if(isEnd){
		scaleVal += 0.01*(0-scaleVal);
	}else {
		scaleVal += 0.001*(1-scaleVal);
	}
	rotateVal+=0.05;
	//if(rotateVal>360)rotateVal=0;
}