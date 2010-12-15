/*
 *  KiraParticleChid.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "KiraParticleChid.h"

int life_Full = 15;

KiraParticleChid::KiraParticleChid(){
	x=0;
	y=0;
	life = life_Full;
}

void KiraParticleChid::setup() {
	
}

void KiraParticleChid::generateAtPoint(int px, int py){
	x=px;
	y=py;
	vx = -2+rand()%4;
	vy = -2+rand()%4;
	life = life_Full;
	r=0;
}


void KiraParticleChid::update() {
	//y-=1.2;
	y += vy;
	x += vx;
	life-=1;
	r+=10;
	if(life<0)life=0;
}
void KiraParticleChid::draw() {
	
}