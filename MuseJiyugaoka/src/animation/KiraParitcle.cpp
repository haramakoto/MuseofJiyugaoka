/*
 *  KiraParitcle.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "KiraParitcle.h"

KiraParitcle::KiraParitcle(){
	int i;
	for(i=0; i<60; i++){
		particles.push_back(KiraParticleChid());
	}
	twincle.loadImage("twinkle.png");
}

void KiraParitcle::setup() {
	x = 800;
	y = 600;
}
void KiraParitcle::update() {
	x -= 15;
	y -= 5;
	generateNew(x,y);
	int i;
	for (i=0; i<particles.size(); i++) {
		particles[i].update();
	}
	
	
	if(x<0)x=800;
}
void KiraParitcle::generateNew(float px, float py){
	int i;
	for (i=0; i<particles.size(); i++) {
		if(particles[i].life==0){
			particles[i].generateAtPoint(px, py);
			break;
		}
	}
}
void KiraParitcle::draw() {
	int i;
	for (i=0; i<particles.size(); i++) {
		if(particles[i].life!=0){
			ofPushMatrix();
			
			ofTranslate(particles[i].x,particles[i].y,0);
			//ofRotate(particles[i].r, 0, 0, 1);
			twincle.draw(-50, -50);
			ofPopMatrix();
		}
	}
	
}