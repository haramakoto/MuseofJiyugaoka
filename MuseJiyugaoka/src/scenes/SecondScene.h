/*
 *  SecondScene.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/11/30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "ofMain.h"
#include "RingAnimationObject.h"
#include "RingAnimationPos.h"
#include "Wing.h"

class SecondScene{
public:
	SecondScene();
	
	void update();
	void draw();
	void setup();
	
	void toggleDress();
	void toggleWing();
	void toggleIcon();
	
	bool isDress;
	bool isWing;
	bool isIcon;
	int stageStep;
	
	//Animation Zero Check
	void animeZeroCheck();
	
	//Sound Method
	void updateWithSounds(float *sounds);
	
	//Animation Object List
	std::vector<RingAnimationObject> AniObjectList;
	
	RingAnimationObject AniObj1;
	std::vector<string> AniList1;
	
	
	//Image Animation List
	std::vector<RingAnimationPos> AniPosList;
	
	//Image
	ofImage snow1;
	ofImage angel1;
	ofImage generalBG;
	
	//Wing
	Wing wingR;
	Wing wingL;
	
	//Alpha
	float bgAlpha;
	float iconAlpha;
	
	
	int isFadeOut;
	int imageIndex;
};
