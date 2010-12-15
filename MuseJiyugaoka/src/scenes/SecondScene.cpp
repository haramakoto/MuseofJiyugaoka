/*
 *  SecondScene.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SecondScene.h"

SecondScene::SecondScene(){
	int i;
	
	AniList1.push_back("santa2/santa0001.png");
	AniList1.push_back("santa2/santa0002.png");
	AniList1.push_back("santa2/santa0003.png");
	AniList1.push_back("santa2/santa0004.png");
	AniList1.push_back("santa2/santa0005.png");
	AniList1.push_back("santa2/santa0006.png");
	AniList1.push_back("santa2/santa0007.png");
	AniList1.push_back("santa2/santa0008.png");
	AniList1.push_back("santa2/santa0009.png");
	AniList1.push_back("santa2/santa0010.png");
	AniList1.push_back("santa2/santa0011.png");
	AniList1.push_back("santa2/santa0012.png");
	AniList1.push_back("santa2/santa0013.png");
	AniList1.push_back("santa2/santa0014.png");
	AniList1.push_back("santa2/santa0015.png");
	AniList1.push_back("santa2/santa0016.png");
	AniList1.push_back("santa2/santa0017.png");
	AniList1.push_back("santa2/santa0018.png");
	AniList1.push_back("santa2/santa0019.png");
	AniList1.push_back("santa2/santa0020.png");
	AniList1.push_back("santa2/santa0021.png");
	AniList1.push_back("santa2/santa0022.png");
	AniList1.push_back("santa2/santa0023.png");
	AniList1.push_back("santa2/santa0024.png");
	AniList1.push_back("santa2/santa0025.png");
	AniList1.push_back("santa2/santa0026.png");
	AniList1.push_back("santa2/santa0027.png");
	AniList1.push_back("santa2/santa0028.png");
	AniList1.push_back("santa2/santa0029.png");
	AniList1.push_back("santa2/santa0030.png");
	
	generalBG.loadImage("fab1.png");
	AniObj1.setRingURLList(AniList1);
	
	// add PosList
	
	// s n o w ////////////////////////
	
	RingAnimationPos pos1;
	pos1.setup(0.2, 1);
	pos1.y = 0;
	pos1.x = 5;
	AniPosList.push_back(pos1);
	
	RingAnimationPos pos2;
	pos2.setup(-0.1, 0.5);
	pos2.y = 100;
	pos2.x = 35;
	AniPosList.push_back(pos2);
	
	RingAnimationPos pos3;
	pos3.setup(-0.1, 0.8);
	pos3.y = 200;
	pos3.x = 25;
	AniPosList.push_back(pos3);
	
	RingAnimationPos pos4;
	pos4.setup(-0.3, 0.7);
	pos4.y = 300;
	pos4.x = 15;
	AniPosList.push_back(pos4);
	
	RingAnimationPos pos5;
	pos5.setup(-0.1, 0.5);
	pos5.y = 400;
	pos5.x = 5;
	AniPosList.push_back(pos5);
	
	// a n g e l /////////////////////
	
	RingAnimationPos pos6;
	pos6.setup(0.4, -0.5);
	pos6.y = 100;
	pos6.x = 100;
	AniPosList.push_back(pos6);
	
	RingAnimationPos pos7;
	pos7.setup(0.2, -0.4);
	pos7.y = 100;
	pos7.x = 50;
	AniPosList.push_back(pos7);
	
	snow1.loadImage("snow1.png");
	angel1.loadImage("angel.png");
	
	//wing init
	wingR.initWing(true,2);
	wingL.initWing(false,2);
}	

void SecondScene::setup() {
	AniObj1.x = 0;
	AniObj1.y = 200;
	AniObj1.yOffset = 80;
	AniObj1.setup(-0.1, -0.5);
	stageStep = 0;
	isDress = true;
	isWing = false;
	isIcon = false;
	wingR.setup();
	wingL.setup();
	bgAlpha = 255;
	iconAlpha = 0;
}
void SecondScene::update() {
	if(isFadeOut==1){
		
	}else {
		int i;
		for(i=0; i<AniPosList.size(); i++){
			AniPosList[i].update();
		}
		AniObj1.update();
	}
}

void SecondScene::draw() {
	int i;
	
	// Dress Draw //////////////////
	if(isDress){
		bgAlpha += 0.05*(255-bgAlpha);
	}else {
		bgAlpha += 0.05*(0-bgAlpha);
	}
	ofSetColor(255,255,255,bgAlpha);
	generalBG.draw(0, 0);
	ofSetColor(255,255,255,255);
	
	// icon Draw ///////////////////
	if(isIcon){
		iconAlpha += 0.02*(255-iconAlpha);
	}else {
		iconAlpha += 0.05*(0-iconAlpha);
	}
	
	ofSetColor(255,255,255,iconAlpha);
	
		AniObj1.draw();
	
		for(i=0; i<AniPosList.size(); i++){
			ofPushMatrix();
			ofTranslate(AniPosList[i].x, AniPosList[i].y, 0);
			//ofRotate(AniPosList[i].r, 0, 0, 1);
			ofScale(AniPosList[i].scaleVal, AniPosList[i].scaleVal, 1);

			if(i<6){
				snow1.draw(-10,-10);
			}else {
				angel1.draw(-37, -32);
			}
		
			ofPopMatrix();
		}
	ofSetColor(255,255,255,255);
	
	
	wingR.draw();
	wingL.draw();
	
}

void SecondScene::toggleDress(){
	isDress = !isDress;
}
void SecondScene::toggleWing(){
	isWing = !isWing;
	wingL.isEnd = !wingL.isEnd;
	wingR.isEnd = !wingR.isEnd;
}
void SecondScene::toggleIcon(){
	isIcon = !isIcon;
}

void SecondScene::updateWithSounds(float *sounds){
	
	if(sounds[100]>0.01){
		AniObj1.multipleSpeed(1+sounds[100]*10);
	}else {
		//
	}
	int i;
	int indexUnit = 120 / AniPosList.size()-1;
	for (i=0; i<AniPosList.size(); i++) {
		if(sounds[indexUnit*i]>0.01){
			AniPosList[i].multipleSpeed(1+sounds[indexUnit*i]*10);
		}
	}
	
}
