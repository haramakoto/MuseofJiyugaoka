/*
 *  Animator.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/27.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __TEST_H__
#define __TEST_H__

#include "ofMain.h"

class Animator{
public:
	Animator();
	
	std::vector<ofImage> imageList;
	void setURLList(std::vector<string> urlList);
	void update();
	void draw(float basex, float basey);
	
	int listSize;
	int imageIndex;
	float x;
	float y;
};

#endif __TEST_H__