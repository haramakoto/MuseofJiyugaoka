/*
 *  StartScene.cpp
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/28.
 *
 */

#include "StartScene.h"

StartScene::StartScene(){
	rayCircle.loadImage("scene1_RayCircle.png");
	backGround.loadImage("BlackPlane.png");
	generalBG.loadImage("fab1.png");
	wingR.initWing(true,1);
}

void StartScene::setup() {
	counter = 0;
	circleScale = 0;
	circleAlpha = 255;
	kira.setup();
	wingR.setup();
}
void StartScene::update() {
	if(isFadeOut==1){
		
	}else {
		
	}
	counter++;
}
void StartScene::draw() {
	if(isFadeOut==1){
		
	}else {
		backGround.draw(0, 0);
		//Ray Line up
		if(counter<200){
			kira.update();
			kira.draw();
		}else if (counter<320) {//Flash Bomb
			ofPushMatrix();
			ofTranslate(400, 0, 0);
			ofScale(circleScale, circleScale, 1);
				rayCircle.draw(-400, -400);
			ofPopMatrix();
			circleScale += 0.05;
			if(circleScale>2)circleScale=2;
		}else if (counter<700) {//Bomb Delete / Cloth Appear
			//fadeIn
			ofSetColor(255,255,255,255-circleAlpha);
			generalBG.draw(0, 0);
			//fadeOut
			ofSetColor(255,255,255,circleAlpha);
			ofPushMatrix();
			ofTranslate(400, 0, 0);
			ofScale(circleScale, circleScale, 1);
				rayCircle.draw(-400, -400);
			ofPopMatrix();
			ofSetColor(255,255,255,255);
			circleAlpha--;
			if (circleAlpha<-255) {
				circleAlpha=-255;
			}
		}else{//Wing Appear
			generalBG.draw(0, 0);
			wingR.draw();
		}
	}
}
void StartScene::start() {
	//
}
void StartScene::end() {
	
}