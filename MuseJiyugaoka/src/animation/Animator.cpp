/*
 *  Animator.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/27.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Animator.h"

Animator::Animator(){
	imageIndex = 0;
	listSize = 0;
	x=y=0;
}


void Animator::setURLList(std::vector<string> urlList){
	listSize = urlList.size();
	for (int i=0; i<listSize; i++) {
		ofImage newImage;
		newImage.loadImage(urlList[i]);
		imageList.push_back(newImage);
	}
}

void Animator::update(){
	
}
void Animator::draw(float basex, float basey){
	//ofEnableAlphaBlending();
	imageList[imageIndex].draw(basex,basey);
	//ofDisableAlphaBlending();
	imageIndex++;
	if(imageIndex==listSize)imageIndex=0;
}