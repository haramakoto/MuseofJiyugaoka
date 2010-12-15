#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "Vector3f.h"
#include "Cloth.h"
//#include "MiniObject.h"
#include "MinCharacter.h"
#include "fft.h"
#include "ofxOsc.h"
#include "Animator.h"
#include "StartScene.h"
#include "SecondScene.h"
#include "StandByScene.h"
#include "FourceScene.h"
#include "FifthScene.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void audioReceived(float* input, int bufferSize, int nChannels);
	
		void drawCube();
		void textureChange(int i);
		int textureIndex;
		ofImage blackPlane;
		
		void idleFunc();
		void display();
		void reshape(int w, int h);
		
		GLUquadricObj *quad1;
		float ballPosY;
	
		GLuint LoadTexture(ofImage image);
	
		//MiniObject testPoli;
	
		//Image List
		std::vector<string> ikaList;
		MinCharacter ikaImage;
		Animator ikaImage2D;
	
		//OSC
		ofxOscSender sender;
		ofxOscReceiver receiver;
		string message;
	
		int isStart;
		int PointEditmode;
	
		// Point Edit
		void toggleEditmode();
		void editPointPlus();
		void editPointMinus();
		void editPointYup();
		void editPointYdown();
		void editPointYPlus();
		void editPointYMinus();
	
		//Scene control
		int sceneIndex;
		StandByScene scene0;
		StartScene scene1;
		SecondScene scene2;
		FourceScene scene4;
		FifthScene scene5;
	
		//posSync control
		void syncX();
		void syncY();
		int syncCounter;
		void toggleCurrentDress();
		void toggleCurrentIcon();
		void toggleCurrentWing();
	
		//sounds
		void updateSounds();
};

#endif