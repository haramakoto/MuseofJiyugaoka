/*
 *  StartScene.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "KiraParitcle.h"
#include "Wing.h"

class StartScene{
public:
	StartScene();
	
	void update();
	void draw();
	void setup();
	
	void start();
	void end();
	
	int isFadeOut;
	int counter;
	
	KiraParitcle kira;
	ofImage rayCircle;
	ofImage backGround;
	ofImage generalBG;
	
	Wing wingR;
	
	//params
	float circleScale;
	float circleAlpha;
};
