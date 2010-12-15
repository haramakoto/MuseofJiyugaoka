/*
 *  MinCharacter.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/13.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class MinCharacter{
public:
	MinCharacter();
	
	std::vector<ofImage> imageList;
	void setURLList(std::vector<string> urlList);
	//void setURLList(string urlList[]);
	void update();
	void draw();
	int imageIndex;
	int listSize;
	
	void setRotatePos(float r);
	void start();
	void stop();
	
	int isStart;
	
	float rx;
	float ry;
	float rz;
	float yPos;
	float alphaParam;
	int isClose;
};