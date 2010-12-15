/*
 *  FifthScene.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/12/04.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "FifthScene.h"


FifthScene::FifthScene(){
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
	
	generalBG.loadImage("fab3.png");
	AniObj1.setRingURLList(AniList1);
	
	// add PosList
	
	// r o o f /////////////////////
	
	RingAnimationPos pos6;
	pos6.setup(-1.4, 0);
	pos6.y = 200;
	pos6.x = 0;
	AniPosList.push_back(pos6);
	
	// n o r m a l ////////////////////////
	
	RingAnimationPos pos1;
	pos1.setup(-1.2, 0);
	pos1.y = 300;
	pos1.x = 5;
	AniPosList.push_back(pos1);
	
	RingAnimationPos pos2;
	pos2.setup(-2, 0);
	pos2.y = 400;
	pos2.x = 35;
	AniPosList.push_back(pos2);
	
	RingAnimationPos pos3;
	pos3.setup(-0.8, 0);
	pos3.y = 500;
	pos3.x = 25;
	AniPosList.push_back(pos3);
	
	RingAnimationPos pos4;
	pos4.setup(-1.3, 0);
	pos4.y = 600;
	pos4.x = 15;
	AniPosList.push_back(pos4);
	
	RingAnimationPos pos5;
	pos5.setup(-0.6, 0);
	pos5.y = 700;
	pos5.x = 5;
	AniPosList.push_back(pos5);
	
	star1.loadImage("star1.png");
	star2.loadImage("star1.png");
	
	//wing init
	wingR.initWing(true,5);
	wingL.initWing(false,5);
}	

void FifthScene::setup() {
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
	bgAlpha = 0;
	iconAlpha = 0;
}
void FifthScene::update() {
	if(isFadeOut==1){
		
	}else {
		int i;
		for(i=0; i<AniPosList.size(); i++){
			AniPosList[i].update();
		}
		AniObj1.update();
	}
}

void FifthScene::draw() {
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
		ofRotate(AniPosList[i].r, 0, 0, 1);
		ofScale(AniPosList[i].scaleVal, AniPosList[i].scaleVal, 1);
		if(i<1){
			star2.draw(-37, -32);
		}else {
			star1.draw(-10,-10);
		}
		
		ofPopMatrix();
	}
	ofSetColor(255,255,255,255);
	
	
	wingR.draw();
	wingL.draw();
	
}

void FifthScene::toggleDress(){
	isDress = !isDress;
}
void FifthScene::toggleWing(){
	isWing = !isWing;
	wingL.isEnd = !wingL.isEnd;
	wingR.isEnd = !wingR.isEnd;
}
void FifthScene::toggleIcon(){
	isIcon = !isIcon;
}

void FifthScene::updateWithSounds(float *sounds){
	if(sounds[100]>0.2){
		AniObj1.multipleSpeed(1+sounds[100]*20);
	}
	int i;
	int indexUnit = 120 / AniPosList.size()-1;
	for (i=0; i<AniPosList.size(); i++) {
		if(sounds[indexUnit*i]>0.2){
			AniPosList[i].multipleSpeed(1+sounds[indexUnit*i]*20);
		}		
	}
	
}
