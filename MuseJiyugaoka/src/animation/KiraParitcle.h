/*
 *  KiraParitcle.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofMain.h"
#include "KiraParticleChid.h"

class KiraParitcle{
public:
	KiraParitcle();
	
	std::vector<KiraParticleChid> particles;
	ofImage twincle;
	
	void update();
	void generateNew(float px, float py);
	void draw();
	void setup();
	float x,y;
};