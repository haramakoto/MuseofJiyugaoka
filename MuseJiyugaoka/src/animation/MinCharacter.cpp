/*
 *  MinCharacter.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/13.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MinCharacter.h"

MinCharacter::MinCharacter(){
	imageIndex = 0;
	listSize = 0;
	rx = 0;
	ry = 0;
	rz = 0;
	yPos = 0;
	isStart = 0;
	alphaParam = 0;
	isClose = 0;
}

//void MiniCharacter::setURLList(std::vector<string> urlList){
void MinCharacter::setURLList(std::vector<string> urlList){
	listSize = urlList.size();
	for (int i=0; i<listSize; i++) {
		ofImage newImage;
		newImage.loadImage(urlList[i]);
		imageList.push_back(newImage);
	}
}

void MinCharacter::setRotatePos(float r){
	rx = ry = rz = r;
}
void MinCharacter::start(){
	isStart = 1;
	isClose = 0;
}
void MinCharacter::stop(){
	isClose = 1;
}

void MinCharacter::update(){
	
}
void MinCharacter::draw(){
	if(isStart==0)return;
	
	glPushMatrix();
	glTranslatef(rx, 10, 0);
	
	ofSetColor(255,255,255,alphaParam);
	
	imageList[imageIndex].draw(0,0);
	
	glPopMatrix();
	
	imageIndex++;
	if(imageIndex==listSize)imageIndex=0;
	
	if(alphaParam>255)alphaParam=255;
	if(alphaParam<0)alphaParam=0;
	
	if(isClose){
		alphaParam-=1;
	}else {
		alphaParam+=1;
	}

	rx += 0.5;
	ry += 0.5;
}