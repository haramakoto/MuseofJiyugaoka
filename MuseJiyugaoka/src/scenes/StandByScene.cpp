/*
 *  StandByScene.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/12/03.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "StandByScene.h"

StandByScene::StandByScene(){
	int i;
	
	AniList1.push_back("santa/santa0001.png");
	AniList1.push_back("santa/santa0002.png");
	AniList1.push_back("santa/santa0003.png");
	AniList1.push_back("santa/santa0004.png");
	AniList1.push_back("santa/santa0005.png");
	AniList1.push_back("santa/santa0006.png");
	AniList1.push_back("santa/santa0007.png");
	AniList1.push_back("santa/santa0008.png");
	AniList1.push_back("santa/santa0009.png");
	AniList1.push_back("santa/santa0010.png");
	AniList1.push_back("santa/santa0011.png");
	AniList1.push_back("santa/santa0012.png");
	AniList1.push_back("santa/santa0013.png");
	AniList1.push_back("santa/santa0014.png");
	AniList1.push_back("santa/santa0015.png");
	AniList1.push_back("santa/santa0016.png");
	AniList1.push_back("santa/santa0017.png");
	AniList1.push_back("santa/santa0018.png");
	AniList1.push_back("santa/santa0019.png");
	AniList1.push_back("santa/santa0020.png");
	AniList1.push_back("santa/santa0021.png");
	AniList1.push_back("santa/santa0022.png");
	AniList1.push_back("santa/santa0023.png");
	AniList1.push_back("santa/santa0024.png");
	AniList1.push_back("santa/santa0025.png");
	AniList1.push_back("santa/santa0026.png");
	AniList1.push_back("santa/santa0027.png");
	AniList1.push_back("santa/santa0028.png");
	AniList1.push_back("santa/santa0029.png");
	AniList1.push_back("santa/santa0030.png");
	
	generalBG.loadImage("dummyBG.png");
	AniObj1.setRingURLList(AniList1);
	
	// add PosList
	
	// s n o w ////////////////////////
	
	RingAnimationPos pos1;
	pos1.setup(-1, 0);
	pos1.y = 240;
	pos1.x = 5;
	AniPosList.push_back(pos1);
	
	RingAnimationPos pos2;
	pos2.setup(-0.8, 0);
	pos2.y = 370;
	pos2.x = 35;
	AniPosList.push_back(pos2);
	
	// a n g e l /////////////////////
	
	RingAnimationPos pos6;
	pos6.vx = 0.4;
	pos6.vy = -0.5;
	pos6.y = 100;
	pos6.x = 100;
	AniPosList.push_back(pos6);
	
	RingAnimationPos pos7;
	pos7.vx = 0.2;
	pos7.vy = -0.4;
	pos7.y = 100;
	pos7.x = 50;
	AniPosList.push_back(pos7);
	
	
	artmeter.loadImage("artMeter.png");
	e_p.loadImage("epLogo.png");
	
	//wing init
	wingR.initWing(true,0);
	wingL.initWing(false,0);
}	

void StandByScene::setup() {
	AniObj1.x = 0;
	AniObj1.y = 200;
	AniObj1.yOffset = 80;
	stageStep = 0;
	isDress = true;
	isWing = false;
	isIcon = false;
	wingR.setup();
	wingL.setup();
	bgAlpha = 0;
	iconAlpha = 0;
}
void StandByScene::update() {
	if(isFadeOut==1){
		
	}else {
		int i;
		for(i=0; i<AniPosList.size(); i++){
			AniPosList[i].update();
		}
	}
}

void StandByScene::draw() {
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
	
	//AniObj1.draw();
	
	for(i=0; i<AniPosList.size(); i++){
		ofPushMatrix();
		ofTranslate(AniPosList[i].x, AniPosList[i].y, 0);
		ofRotate(AniPosList[i].r, 0, 0, 1);
		ofScale(AniPosList[i].scaleVal, AniPosList[i].scaleVal, 1);
		if(i<1){
			artmeter.draw(-10,-10);
		}else {
			e_p.draw(-37, -32);
		}
		
		ofPopMatrix();
	}
	ofSetColor(255,255,255,255);
	
	
	wingR.draw();
	wingL.draw();
	
}

void StandByScene::toggleDress(){
	isDress = !isDress;
}
void StandByScene::toggleWing(){
	isWing = !isWing;
	wingL.isEnd = !wingL.isEnd;
	wingR.isEnd = !wingR.isEnd;
}
void StandByScene::toggleIcon(){
	isIcon = !isIcon;
}

void StandByScene::updateWithSounds(float *sounds){
	if(sounds[100]>0.2){
		AniObj1.applyScale(1+sounds[100]*2);
	}else {
		AniObj1.applyScale(1);
	}
	int i;
	int indexUnit = 120 / AniPosList.size()-1;
	for (i=0; i<AniPosList.size(); i++) {
		if(sounds[indexUnit*i]>0.2){
			AniPosList[i].applyScale(1+sounds[indexUnit*i]*2);
		}else {
			AniPosList[i].applyScale(1);
		}
		
	}
	
}
