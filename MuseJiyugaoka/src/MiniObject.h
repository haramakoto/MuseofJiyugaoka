/*
 *  MiniObject.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/06.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "Vector3f.h"
#include "Particle.h"

class MiniObject{
public:
	MiniObject();
	
	void update();
	void draw();
	void setup(string imagepath);
	void drawTriangle(const Particle p1, const Particle p2, const Particle p3, int isFront, float blockX, float blockY);
	ofImage myTexture;
	
	Particle p1,p2,p3,p4;
};

