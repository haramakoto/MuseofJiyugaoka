/*
 *  MiniObject.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/06.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MiniObject.h"

MiniObject::MiniObject(){

}

void MiniObject::setup(string imagepath) {
	myTexture.loadImage(imagepath);
	p1 = Particle(Vector3f(0,0,0),Vector3f(100,100,100));
	p2 = Particle(Vector3f(320,0,0),Vector3f(100,100,100));
	p3 = Particle(Vector3f(320,91,0),Vector3f(100,100,100));
	p4 = Particle(Vector3f(0,91,0),Vector3f(100,100,100));
}

void MiniObject::draw() {
	glColor4f(1, 1, 1, 0);
	myTexture.draw(0, 0);
	glColor4f(1, 1, 1, 1);
	
	Vector3f color = Vector3f(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);
	
	glBegin(GL_TRIANGLES);
	glColor3fv(color.getXLocation());
	drawTriangle(p2,p1,p4,0,320,91);
	drawTriangle(p3,p2,p4,1,320,91);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
}

void MiniObject::drawTriangle(const Particle pp1, const Particle pp2, const Particle pp3, int isFront, float blockX, float blockY){
	ofxVec2f t1;
	ofxVec2f t2;
	ofxVec2f t3;
	
	int x=0;
	int y=0;
	
	if (isFront==0) {
		t1 = ofxVec2f((x+1) * blockX, y * blockY);
		t2 = ofxVec2f(x * blockX, y * blockY);
		t3 = ofxVec2f(x * blockX, (y+1) * blockY);
	}else {
		t1 = ofxVec2f((x+1) * blockX, (y+1) * blockY);
		t2 = ofxVec2f((x+1) * blockX, y * blockY);
		t3 = ofxVec2f(x * blockX, (y+1) * blockY);
	}
	
	//glTexCoord2fv(t1.v);
	glNormal3fv(pp1.getNormal().getXLocation());
	glVertex3fv(pp1.getPosition().getXLocation());
	
	//glTexCoord2fv(t2.v);
	glNormal3fv(pp2.getNormal().getXLocation());
	glVertex3fv(pp2.getPosition().getXLocation());
	
	//glTexCoord2fv(t3.v);
	glNormal3fv(pp3.getNormal().getXLocation());
	glVertex3fv(pp3.getPosition().getXLocation());
	
}

void MiniObject::update() {
	Particle *pp1 = &p1;
	Particle *pp2 = &p2;
	Particle *pp3 = &p3;
	Particle *pp4 = &p4;
	pp1->setNormal(Vector3f(0,0,0));
	pp2->setNormal(Vector3f(0,0,0));
	pp3->setNormal(Vector3f(0,0,0));
	pp4->setNormal(Vector3f(0,0,0));
}


