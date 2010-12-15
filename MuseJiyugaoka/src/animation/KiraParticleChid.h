/*
 *  KiraParticleChid.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"

class KiraParticleChid{
public:
	KiraParticleChid();
	
	void update();
	void draw();
	void setup();
	void generateAtPoint(int px, int py);
	int life;
	float x,y,r,vx,vy;
};
