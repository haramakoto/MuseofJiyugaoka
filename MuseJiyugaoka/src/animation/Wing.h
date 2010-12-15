/*
 *  Wing.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __WING_H__
#define __WING_H__

#include "ofMain.h"

class Wing{
public:
	Wing();
	
	ofImage WingBody;
	bool L_R;
	
	void update();
	void draw();
	void setup();
	void initWing(bool lr,int sceneIndex);
	
	std::vector<string> LWingList;
	std::vector<string> RWingList;
	
	float scaleVal;
	float rotateVal;
	
	bool isEnd;
};

#endif __WING_H__