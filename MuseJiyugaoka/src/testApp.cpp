#include "testApp.h"
#define MAP_X 512
#define MAP_Z 512

#define _CONTROLLER


unsigned long lastUpdate;	// When was the last time we updated the cloth position
Cloth cloth(280,280,36,36);		// The cloth fabric were operating on
Vector3f ball_pos(40, -160,45);	// The location of the Ball the cloth lands on
Vector3f ball_pos2(60, -30,25);
Vector3f ball_pos3(80, -30,25);
float ball_radius = 26;		// The size of the ball
bool started = false;		// Wait until space bar has been pressed before dropping the cloth
ofImage myImage;
GLuint gltexture;

float *audio_input = NULL;
float *magnitude, *phase, *power;
std::vector<float> magnitudeVect;
float *magnitude_average, *magnitude_average_snapshot;
int buffer_size = 1024, fft_size = 512;
fft myfft;


//--------------------------------------------------------------
void testApp::setup(){
	int i;
	isStart = 0;
	
	ofSetFrameRate(60);
	//ofSetFullscreen(true);
	
	blackPlane.loadImage("fab1.png");
	
	// mode ________//////////////////////////
	PointEditmode=0;
	
	started = true;
	
	cloth.setUpCloth();
	
	//texture etc. ///////////////////////////
	textureIndex = 0;
	
	//ball position Init
	ballPosY = 0;
	
	
	reshape(800, 600);
	
	//Sound Function//////////////////////////////////////////////////
	audio_input = new float[buffer_size];
	magnitude = new float[fft_size];
	phase = new float[fft_size];
	power = new float[fft_size];
	magnitude_average = new float[fft_size];
	magnitude_average_snapshot = new float[fft_size];
	for (int i = 0; i < fft_size; i++)
	{
		magnitude[i] = 0;
		phase[i] = 0;
		power[i] = 0;
		magnitude_average_snapshot[i] = 0;
		magnitude_average[i] = 0;
		magnitudeVect.push_back(0);
	}
	
	ofSoundStreamSetup(0, 1, this, 44100, buffer_size, 4);	
	//ofSoundStreamListDevices();
	PointEditmode=0;
	
	//OSC
	#ifdef _CONTROLLER
	sender.setup("169.254.3.224",3001);
	receiver.setup(3000);
	
	
	#else
	sender.setup("172.17.10.10",3000);
	receiver.setup(3001);
	#endif
	
	//LR Mode
	#ifdef _CONTROLLER
	cloth.sideMode=1;
	#else
	cloth.sideMode=0;
	#endif
	
	//Scene Control ///______________//
	sceneIndex = 0;
	syncCounter = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
	string maddress;
	#ifdef _CONTROLLER
		//
	#else
		int texIndex;
	
	int i;
	int inverceParam;
		while(receiver.hasWaitingMessages()){
			ofxOscMessage m;
			receiver.getNextMessage(&m);
			if ( m.getAddress() == "/texChange" ){
				texIndex = m.getArgAsInt32(0);
				textureChange(texIndex);
				
			}else if ( m.getAddress() ==  "/allStart"){
				isStart = 1;
				
			}else if ( m.getAddress() ==  "/inVerce"){
				inverceParam = m.getArgAsInt32(0);
				cloth.inverceMathAdd(inverceParam);
				
			}else if ( m.getAddress() ==  "/toggleEditmode"){
				toggleEditmode();
				
			}else if ( m.getAddress() ==  "/editPointPlus"){
				editPointPlus();
				
			}else if ( m.getAddress() ==  "/editPointYup"){
				editPointYup();
				
			}else if ( m.getAddress() ==  "/editPointMinus"){
				editPointMinus();
				
			}else if ( m.getAddress() ==  "/editPointYdown"){
				editPointYdown();
			}else if(m.getAddress()=="/syncX"){
				if(sceneIndex==2){
					for (i=0; i<scene2.AniPosList.size(); i++) {
						scene2.AniPosList[i].x = m.getArgAsFloat(i);
					}
					scene2.AniObj1.x = m.getArgAsFloat(scene2.AniPosList.size());
					scene2.AniObj1.y = m.getArgAsFloat(scene2.AniPosList.size()+1);
				}else if(sceneIndex==4) {
					for (i=0; i<scene4.AniPosList.size(); i++) {
						scene4.AniPosList[i].x = m.getArgAsFloat(i);
					}
					scene4.AniObj1.x = m.getArgAsFloat(scene4.AniPosList.size());
					scene4.AniObj1.y = m.getArgAsFloat(scene4.AniPosList.size()+1);
				}else if(sceneIndex==5) {
					for (i=0; i<scene5.AniPosList.size(); i++) {
						scene5.AniPosList[i].x = m.getArgAsFloat(i);
					}
					scene5.AniObj1.x = m.getArgAsFloat(scene5.AniPosList.size());
					scene5.AniObj1.y = m.getArgAsFloat(scene5.AniPosList.size()+1);
				}
			}else if(m.getAddress()=="/syncY"){
				if(sceneIndex==2){
					for (i=0; i<scene2.AniPosList.size(); i++) {
						scene2.AniPosList[i].y = m.getArgAsFloat(i);
					}
				}else if(sceneIndex==4) {
					for (i=0; i<scene4.AniPosList.size(); i++) {
						scene4.AniPosList[i].y = m.getArgAsFloat(i);
					}
				}else if(sceneIndex==5) {
					for (i=0; i<scene5.AniPosList.size(); i++) {
						scene5.AniPosList[i].y = m.getArgAsFloat(i);
					}
				}
			}else if (m.getAddress()=="/toggleDress") {
				toggleCurrentDress();
			}else if (m.getAddress()=="/toggleIcon") {
				toggleCurrentIcon();
			}else if (m.getAddress()=="/toggleWing") {
				toggleCurrentWing();
			}else if (m.getAddress()=="/sceneChange") {
				switch (m.getArgAsInt32(0)) {
					case 0:
						scene0.setup();
						sceneIndex = 0;
						break;
					case 1:
						scene1.setup();
						sceneIndex = 1;
						break;
					case 2:
						scene2.setup();
						sceneIndex = 2;
						break;
					case 4:
						scene4.setup();
						sceneIndex = 4;
						break;
					case 5:
						scene5.setup();
						sceneIndex = 5;
						break;
					default:
						break;
				}
			}else if(m.getAddress()=="/soundChange") {
				for (i = 0; i < fft_size; i++)
				{
					magnitude[i] = m.getArgAsFloat(i);
				}
				updateSounds();
			}else{
				
			}
		}
	#endif
	
	if(isStart==0)return;
	
	ballPosY+=0.01;
	
	// Scene Control ___////////////////////
	switch (sceneIndex) {
		case 0:
			scene0.update();
			break;
		case 1:
			scene1.update();
			break;
		case 2:
			scene2.update();
		case 4:
			scene4.update();
			break;
		case 5:
			scene5.update();
			break;

			break;
		default:
			break;
	}
	
	// Sync Control ___////////////////////
	syncCounter++;
	if(syncCounter==30){
		#ifdef _CONTROLLER
			syncX();
			syncY();
		#else
		
		#endif
		
		syncCounter=0;
	}
}

// load a 256x256 RGB .RAW file as a texture
GLuint testApp::LoadTexture(ofImage image)
{	
	unsigned char* texturedata;
	
	texturedata = image.getPixels();
	
    GLuint texture;
	bool wrap = true;
	
    // allocate a texture name
    glGenTextures( 1, &texture );
	
    // select our current texture
    glBindTexture( GL_TEXTURE_2D, texture );
	
    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_NEAREST );
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
					wrap ? GL_REPEAT : GL_CLAMP );
	
    // build our texture mipmaps
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, MAP_X, MAP_Z,
					  GL_RGB, GL_UNSIGNED_BYTE, texturedata );
	
    return texture;
}


//--------------------------------------------------------------
void testApp::draw(){
	if(isStart==0)return;
	
	glEnable(GL_TEXTURE_2D);
	ofEnableAlphaBlending();
	
	float vpw=ofGetWidth();
	float vph=ofGetHeight();
	
	glClearColor(0,0,0,0);//	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//draw 2D Texture_______////////////////////////////////////////////
	switch (sceneIndex) {
		case 0:
			scene0.draw();
			break;
		case 1:
			scene1.draw();
			break;
		case 2:
			scene2.draw();
			break;
		case 4:
			scene4.draw();
			break;
		case 5:
			scene5.draw();
			break;
		default:
			break;
	}
	
	// status  __________________///////////////////
	/*ofSetColor(255, 255, 255);
	string info = "FPS: "+ofToString(ofGetFrameRate());
	info += "\nEditMode: "+ofToString(PointEditmode);
	info += "\nPress [space] to capture background.";
	info += "\nPress [+/-] to change threshold";
	info += "\nPress [1/2] to change simple amount";
	ofDrawBitmapString(info, 20, 20);*/
	// __________________/////////////////// status
	
	
	//setting 3D view port------------------------
	glEnable(GL_DEPTH_TEST);
	glViewport(0 , 0 , vpw, vph);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, vpw / vph, 2.0, 200000.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Camera Position
	
	#ifdef _CONTROLLER
	gluLookAt(0,-220,2060, 0,-220,0, 0,1,0);
	glRotatef(80.859375,0,1,0);
	glRotatef(-2.343750,1,0,0);
	
	#else
	gluLookAt(0,-220,1860, 0,-220,0, 0,1,0);
	glRotatef(-124.667969,0,1,0);
	glRotatef(5.566406,1,0,0);
	
	#endif
	
	glPushMatrix();
	glPopMatrix();
	
	//cloth draw//////////////////////////////////
	idleFunc();
	display();
	
	// return to initState
	glDisable(GL_DEPTH_TEST);
	
}
void testApp::drawCube()
{
	glColor4f(1,1,1,.6);
	glBegin(GL_POLYGON);
	glVertex3f(-50,-50,-50);
	glVertex3f( 50,-50,-50);
	glVertex3f( 50, 50,-50);
	glColor4f(1,0,0,.6);
	glVertex3f(-50, 50,-50);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glColor4f(1,0,0,.6);
	glVertex3f(-50,-50, 50);
	glVertex3f( 50,-50, 50);
	glVertex3f( 50, 50, 50);
	glColor4f(1,1,1,.6);
	glVertex3f(-50, 50, 50);
	glEnd();
	
	glBegin(GL_LINES);
	glColor4f(1,1,1,.6);
	glVertex3f(-50,-50,-50);
	glColor4f(1,0,0,.6);
	glVertex3f(-50,-50, 50);
	
	glColor4f(1,1,1,.6);
	glVertex3f( 50,-50,-50);
	glColor4f(1,0,0,.6);
	glVertex3f( 50,-50, 50);
	
	glColor4f(1,1,1,.6);
	glVertex3f( 50, 50,-50);
	glColor4f(1,0,0,.6);
	glVertex3f( 50, 50, 50);
	
	glColor4f(1,0,0,.6);
	glVertex3f(-50, 50,-50);
	glColor4f(1,1,1,.6);
	glVertex3f(-50, 50, 50);
	glEnd();
}

//--------------------------------------------------------------
void testApp::idleFunc() {
	// If the cloth has been droppede
	if (started) {
		// Apply a wind force to the cloth and calculate the pull of neighbouring particles
		cloth.calculateForces(Vector3f(0.0, 0.1,0.0),ball_pos,ball_pos,ball_pos, ball_radius);
		
		// Get the current time so we can calculate how much time since the last update
		// used when integrating the distance a particle has traveled
		unsigned long currentUpdate = glutGet(GLUT_ELAPSED_TIME);
		
		// Move the cloth particles forward in time by how much time passed since the last update
		cloth.update((currentUpdate - lastUpdate)/100.0f);
		lastUpdate = currentUpdate;
	}
}
//--------------------------------------------------------------
void testApp::display() {
//void display() {
	
	// Clear the screen with the blue color set in the init
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	//item1/////////////////////////////////////////////////////////////
	glTranslatef(-94,0,-10);
	
	// Move the scene in front of the camera then rotate it before doing any drawing
	glPushMatrix();
	glTranslatef(-94,485,-10);
	glRotatef(25,0,1,0);
	glScaled(2, 2, 2);
	
	cloth.draw();
	
	// Move the ball then draw
	glPushMatrix();
	glTranslatef(ball_pos.getX(),ball_pos.getY(),ball_pos.getZ());
	
	// Clear the transforms and rotations applied earlier
	glPopMatrix();
	glPopMatrix();
	
	
	//item2////////////////////////////////////////////////////////////
	// Display the new frame
	glutSwapBuffers();
	glutPostRedisplay();
	
}

void testApp::reshape(int w, int h)  
{
	// Adjust the viewport if the user resizes the window
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	if (h==0)  
		gluPerspective(80,(float)w,1.0,5000.0);
	else
		gluPerspective (80,( float )w /( float )h,1.0,5000.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//--------------------------------------------------------------
void testApp::audioReceived(float* input, int bufferSize, int nChannels)
{
	memcpy(audio_input, input, sizeof(float) * bufferSize);
	
	float avg_power = 0.0f;
	
	myfft.powerSpectrum(0, (int)fft_size, audio_input, buffer_size, 
						magnitude, phase, power, &avg_power);
	
	ofxOscMessage m;
	m.setAddress( "/soundChange" );
	
#ifdef _CONTROLLER
	
	for (int i = 0; i < fft_size; i++)
	{
		magnitude[i] = powf(magnitude[i], 0.5);
		m.addFloatArg(magnitude[i]);
	}
	sender.sendMessage( m );
	
	updateSounds();
#else
	
#endif
	
	
}
//--------------------------------------------------------------
void testApp::updateSounds(){
	cloth.updateWithSounds(magnitude);
	switch (sceneIndex) {
		case 2:
			scene2.updateWithSounds(magnitude);
			break;
		case 4:
			scene4.updateWithSounds(magnitude);
			break;
		case 5:
			scene5.updateWithSounds(magnitude);
			break;
		default:
			break;
	}
}
//--------------------------------------------------------------
void testApp::textureChange(int i){
	printf("texture\n");
	cloth.textureChange(i);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){
	ofxOscMessage m;
	printf("key==----------------   %d\n", key);
	switch (key){
			
        case ' ':

            break;
        case '+':

            break;
        case '0':
			#ifdef _CONTROLLER
				m.setAddress( "/sceneChange" );
				m.addIntArg( 0 );
				sender.sendMessage( m );
			
				scene0.setup();
				sceneIndex = 0;
			#else
			
			#endif
            break;
        case '1':
			#ifdef _CONTROLLER
				m.setAddress( "/sceneChange" );
				m.addIntArg( 1 );
				sender.sendMessage( m );
			
				scene1.setup();
				sceneIndex = 1;
			#else
			
			#endif
            break;
        case '2':
			#ifdef _CONTROLLER
				m.setAddress( "/sceneChange" );
				m.addIntArg( 2 );
				sender.sendMessage( m );
			
				scene2.setup();
				sceneIndex = 2;
			#else
			
			#endif
            break;
		case '4':
			#ifdef _CONTROLLER
				m.setAddress( "/sceneChange" );
				m.addIntArg( 4 );
				sender.sendMessage( m );
			
				scene4.setup();
				sceneIndex = 4;
			#else
			
			#endif
			break;
		case '5':
			#ifdef _CONTROLLER
				m.setAddress( "/sceneChange" );
				m.addIntArg( 5 );
				sender.sendMessage( m );
				
				scene5.setup();
				sceneIndex = 5;
			#else
			
			#endif
			break;

        case 'p':
			cloth.positionAdd(1);
            break;
		case 'q':
			cloth.positionAdd(-1);
            break;
		case 'i':
			#ifdef _CONTROLLER
				cloth.inverceMathAdd(1);
				m.setAddress( "/inVerce" );
				m.addIntArg( 1 );
				sender.sendMessage( m );
			#else
			
			#endif
            break;
		case 'o':
			#ifdef _CONTROLLER
				cloth.inverceMathAdd(-1);
				m.setAddress( "/inVerce" );
				m.addIntArg( -1 );
				sender.sendMessage( m );
			#else
			
			#endif
            break;
		case 's':
			#ifdef _CONTROLLER
				m.setAddress( "/allStart" );
				m.addIntArg( 1 );
				sender.sendMessage( m );
				isStart = 1;
			#else
			
			#endif
			break;
		case 't':
			#ifdef _CONTROLLER
				m.setAddress( "/texChange" );
				m.addIntArg( 0 );
				sender.sendMessage( m );
				textureChange(0);
			#else
			
			#endif
			//textureIndex++;
            break;
		case 'y':
			#ifdef _CONTROLLER
				m.setAddress( "/texChange" );
				m.addIntArg( 1 );
				sender.sendMessage( m );
				textureChange(1);
			#else
			
			#endif
			break;
		case 'd':
			#ifdef _CONTROLLER
				m.setAddress( "/toggleDress" );
				sender.sendMessage( m );
				toggleCurrentDress();
			#else
			
			#endif
			break;
		case 'f':
			#ifdef _CONTROLLER
				m.setAddress( "/toggleIcon" );
				sender.sendMessage( m );
				toggleCurrentIcon();
			#else
			
			#endif			
			break;
		case 'g':
			#ifdef _CONTROLLER
				m.setAddress( "/toggleWing" );
				sender.sendMessage( m );
				toggleCurrentWing();
			#else
			
			#endif
			
			break;
		case 'e':
			toggleEditmode();
			break;
		case 356: //<<
			editPointPlus();
			break;
		case 357: //^
			editPointYup();
			break;
		case 358: //>>
			editPointMinus();
			break;
		case 359: //v
			editPointYdown();
			break;
		case 44: //<
			editPointYMinus();
			break;
		case 46: //>
			editPointYPlus();
			break;
    }
}

void testApp::toggleCurrentDress(){
	if(sceneIndex==2){
		scene2.toggleDress();
	}else if (sceneIndex==0) {
		scene0.toggleDress();
	}else if (sceneIndex==4) {
		scene4.toggleDress();
	}else if (sceneIndex==5) {
		scene5.toggleDress();
	}else {
		//
	}
}
void testApp::toggleCurrentIcon(){
	if(sceneIndex==2){
		scene2.toggleIcon();
	}else if (sceneIndex==0) {
		scene0.toggleIcon();
	}else if (sceneIndex==4) {
		scene4.toggleIcon();
	}else if (sceneIndex==5) {
		scene5.toggleIcon();
	}else {
		//
	}
}
void testApp::toggleCurrentWing(){
	if(sceneIndex==2){
		scene2.toggleWing();
	}else if (sceneIndex==0) {
		scene0.toggleWing();
	}else if (sceneIndex==4) {
		scene4.toggleWing();
	}else if (sceneIndex==5) {
		scene5.toggleWing();
	}else {
		//
	}
}


/// Sync ______////////////////////////////////////////
void testApp::syncX(){
	int i;
	ofxOscMessage m;
	
	switch (sceneIndex) {
		case 0:
			
			break;
		case 1:
			
			break;
		case 2:
			m.setAddress( "/syncX" );
			for (i=0; i<scene2.AniPosList.size(); i++) {
				m.addFloatArg(scene2.AniPosList[i].x);
			}
			//santa
			m.addFloatArg(scene2.AniObj1.x);
			m.addFloatArg(scene2.AniObj1.y);
			
			sender.sendMessage( m );
			
			break;
		case 3:
			
			break;
		case 4:
			m.setAddress( "/syncX" );
			for (i=0; i<scene4.AniPosList.size(); i++) {
				m.addFloatArg(scene4.AniPosList[i].x);
			}
			//santa
			m.addFloatArg(scene4.AniObj1.x);
			m.addFloatArg(scene4.AniObj1.y);
			sender.sendMessage( m );
			break;
		case 5:
			m.setAddress( "/syncX" );
			for (i=0; i<scene5.AniPosList.size(); i++) {
				m.addFloatArg(scene5.AniPosList[i].x);
			}
			//santa
			m.addFloatArg(scene5.AniObj1.x);
			m.addFloatArg(scene5.AniObj1.y);
			sender.sendMessage( m );
			break;

		default:
			break;
	}	
}

void testApp::syncY(){
	int i;
	ofxOscMessage m;
	m.setAddress( "/syncY" );
	switch (sceneIndex) {
		case 0:
			
			break;
		case 1:
			
			break;
		case 2:
			for (i=0; i<scene2.AniPosList.size(); i++) {
				m.addFloatArg(scene2.AniPosList[i].y);
			}
			sender.sendMessage( m );
			break;
		case 3:
			
			break;
		case 4:
			for (i=0; i<scene4.AniPosList.size(); i++) {
				m.addFloatArg(scene4.AniPosList[i].y);
			}
			sender.sendMessage( m );
			break;
		case 5:
			for (i=0; i<scene5.AniPosList.size(); i++) {
				m.addFloatArg(scene5.AniPosList[i].y);
			}
			sender.sendMessage( m );
			break;
			
		default:
			break;
	}
	
}
/// Edit Point Methods ______//////////////////////////

void testApp::toggleEditmode(){
	PointEditmode++;
	if (PointEditmode==2) {
		PointEditmode=0;
	}
	cloth.plotRadiusList();
}
void testApp::editPointPlus(){
	if (PointEditmode==1) {
		cloth.modRadiusAtPoint(10);
	}
}
void testApp::editPointMinus(){
	if (PointEditmode==1) {
		cloth.modRadiusAtPoint(-10);
	}
}
void testApp::editPointYMinus(){
	if (PointEditmode==1) {
		cloth.modYAtPoint(-10);
	}
}
void testApp::editPointYPlus(){
	if (PointEditmode==1) {
		cloth.modYAtPoint(10);
	}
}

void testApp::editPointYup(){
	if (PointEditmode==1) {
		cloth.setModiablePointIndex(cloth.modifyIndex-1);
	}
}
void testApp::editPointYdown(){
	if(PointEditmode==1){
		cloth.setModiablePointIndex(cloth.modifyIndex+1);
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

