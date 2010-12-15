/*
 *  XmlManager.h
 *  PolyTest1
 *
 *  Created by Hara Makoto on 10/12/04.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#include "ofMain.h"
#include "ofxXmlSettings.h"

class XmlManager{
public:
	XmlManager();
	
	ofxXmlSettings XML;
	
	void update();
	void draw();
	void setup();
	
	void saveCalibrarionList();
	void loadCalibrationList();
	void saveCameraPosition();
	void loadCameraPosition();
	void saveDefaultDebugStatus(bool status);
	bool readDefaultDebugStatus();
	
};