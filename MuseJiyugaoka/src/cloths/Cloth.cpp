#include "Cloth.h"

float blockX;
float blockY;
int modPointX = 18;
const GLfloat lightPos[] = { 40 , 0 , 40 , 0 };
const GLfloat lightCol[] = { 10 , 10 , 10 , 100 };
float staticPointList[] = { -20.0,40.0,60.0,70.0,80.0,90.0,100.0,100.0,120.0,110.0,120.0,120.0,140.0,140.0,160.0,160.0,200.0,210.0,220.0,250.0,250.0,270.0,270.0,270.0,270.0,280.0,280.0,280.0,310.0,330.0,340.0,330.0,430.0,410.0,260.0,40.0};

ofVideoPlayer vidPlayer;
static const int VIDEO_WIDTH = 320, VIDEO_HEIGHT = 180;


// Constructors
Cloth::Cloth(float width, float height, int particles_in_width, int particles_in_height)
 : m_width(particles_in_width), m_height(particles_in_height), m_dimensionWidth(width), m_dimensionHeight(height),
   m_distanceX(width/ (float)particles_in_width), m_distanceY(height/(float)particles_in_height)
{

	// Set the particle array to the given size
	m_particles.resize(m_width*m_height);

	// Create the particles to simulate the cloth
	for (int x = 0; x < m_width; ++x) {
		for (int y=0; y < m_height; ++y) {
			// Place the particles of the cloth, lift the edges to give the wind more effect as the cloth falls
			Vector3f position = Vector3f(m_dimensionWidth * (x / (float)m_width),
										 ((x==0)||(x==m_width-1)||(y==0)||(y==m_height-1)) ? m_distanceY/2.0f:0,
										 m_dimensionHeight * (y / (float)m_height));
			// The gravity effect is applied to new particles
			m_particles[y * m_width + x] = Particle(position,Vector3f(0,-0.06,0));
		}
	}
	
	// Calculate the normals for the first time so the initial draw is correctly lit
	collCounter = 0;
	calculateClothNormals();
	counterX=counterY=4;
	textureIndex = 0;
	textureVidMode = 0;
	offsetX = 0;
	offsetZ = 0;
	
	editableX = 10;
	editableY = 0;
	
	modifyIndex = 0;
	sideMode = 0;
	
	int i;
	
	// radius List setup ///////////////////////////////////
	for(i=0; i<particles_in_height; i++){
		radiusList.push_back(staticPointList[i]);
	}
	// yAdditional List setup //////////////////////////////
	for(i=0; i<particles_in_height; i++){
		yAdditionalList.push_back(0);
	}
	
	//parameter for modify_______///////////////////////////
	modParam = -195;
}


// Calculates the normals of all the particles
void Cloth::calculateClothNormals(){
	// For each quad
	for (int x = 0; x < m_width -1; ++x) {
		for (int y =0; y < m_height-1; ++y)
		{
			// Calculate the normals of both triangles and apply the normal to the particles
			Vector3f normal = calculateTriangleCross(*getParticle(x+1, y), *getParticle(x,y), *getParticle(x, y+1));
			getParticle(x+1, y)->addNormal(normal);
			getParticle(x,y)->addNormal(normal);
			getParticle(x,y+1)->addNormal(normal);

			normal = calculateTriangleCross(*getParticle(x+1, y+1), *getParticle(x+1,y), *getParticle(x, y+1));
			getParticle(x+1,y+1)->addNormal(normal);
			getParticle(x+1,y)->addNormal(normal);
			getParticle(x,y+1)->addNormal(normal);
		}
	}
	
	// Normalize the particle normals so they are unit length
	int num = (int)m_particles.size();
	#pragma omp parallel for
	for (int i=0; i<num; ++i)
	{
		m_particles[i].setNormal(m_particles[i].getNormal().normalized());
	}
}

void Cloth::setModiablePointIndex(int i){
	if(i<0){
		modifyIndex=0;
	}else if (i>m_width-1) {
		i=m_width-1;
	}else {
		modifyIndex=i;
	}
}
//modify Radius at Point
void Cloth::modRadiusAtPoint(float s){
	radiusList[modifyIndex]+=s;
}

void Cloth::modYAtPoint(float s){
	yAdditionalList[modifyIndex]+=s;
}

// Used to find normals of a triangle
Vector3f Cloth::calculateTriangleCross(const Particle& p1, const Particle& p2, const Particle& p3) 
{
	return Vector3f(p2.getPosition() - p1.getPosition()).cross(Vector3f(p3.getPosition() - p1.getPosition())).normalized();
}

// Texture Change
void Cloth::textureChange(int i){
	textureIndex++;
	switch (i) {
		case 0:
			imageTextureSetup("fab1.png");
			textureVidMode=0;
			break;
		case 1:
			videoTextureSetup("Movie.m4v");
			textureVidMode=1;
			break;

		default:
			break;
	}
}


// Gets a particle from the particle array
Particle* Cloth::getParticle(int x, int y){
	return &m_particles[y * m_width + x];
}

// Gets a particle from the particle array
const Particle* Cloth::getProtectedParticle(int x, int y) const{
	return &m_particles[y * m_width + x];
}
void Cloth::imageTextureSetup(string url){
	clothTexture.loadImage(url);
	img_width = clothTexture.width;
	img_height = clothTexture.height;
}
void Cloth::videoTextureSetup(string url){
	vidPlayer.loadMovie(url);
	vidPlayer.play();
	img_width = acc_image.width;
	img_height = acc_image.height;
}
void Cloth::setUpCloth() {
	clothTexture.loadImage("fab1.png");
	
	/// ++ video ++ * *  . . . .
	vidPlayer.loadMovie("testmovie.mov");
	vidPlayer.play();
	
	acc_image.allocate(VIDEO_WIDTH, VIDEO_HEIGHT);
	
	myTexture = clothTexture.getTextureReference();
	myTextureData = myTexture.getTextureData();
	
	//texture setup/////////////////////////////////
	m_bpp = clothTexture.bpp;
	img_width = clothTexture.width;
	img_height = clothTexture.height;
	// Determine format
    int fileFormat, internalFormat;
    switch(m_bpp){
        case 24:fileFormat = GL_RGB; internalFormat = GL_RGB; break;
        case 32:fileFormat = GL_RGBA; internalFormat = GL_RGBA; break;
        default:			
			return;
            break;
    }
	// FLIP THE PIXELS
    //we need to flip the image vertically
    unsigned char * ptrToPixels = clothTexture.getPixels();
    int bytesPP = (m_bpp / 8);
	
	//this extra allocation is because of a glu bug - http://osdir.com/ml/video.mesa3d.devel/2005-02/msg00035.html
    unsigned char * flippedPixels = new unsigned char[bytesPP * img_width * (img_height+1)];
    unsigned char * ptrToFlipped = flippedPixels;
	int numBytesPerLine = img_width * bytesPP;
	
	//go to the beginning of the bottom line of pixels of the image
    ptrToPixels += ( numBytesPerLine * (img_height-1) );
	
	for(int y = 0; y < img_height; y++){
        memcpy(ptrToFlipped, ptrToPixels, numBytesPerLine * sizeof( char ) );
        ptrToPixels   -= numBytesPerLine;
        ptrToFlipped  += numBytesPerLine;
    }
	// Light Setting //////////////////////////////////////////
	/*glLightfv(GL_LIGHT0 , GL_POSITION , lightPos);
	glLightfv(GL_LIGHT0 , GL_DIFFUSE , lightCol);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/
	/////////////////////////////////////////// Light Setting//
	
}

// Draws a triangle of the cloth
void Cloth::drawTriangle(const Particle& p1, const Particle& p2, const Particle& p3, const Vector3f& color, int x, int y, int isFront){
	
	ofxVec2f t1;
	ofxVec2f t2;
	ofxVec2f t3;

	if (isFront==0) {
		t1 = ofxVec2f((x+1) * blockX, y * blockY);
		t2 = ofxVec2f(x * blockX, y * blockY);
		t3 = ofxVec2f(x * blockX, (y+1) * blockY);
	}else {
		t1 = ofxVec2f((x+1) * blockX, (y+1) * blockY);
		t2 = ofxVec2f((x+1) * blockX, y * blockY);
		t3 = ofxVec2f(x * blockX, (y+1) * blockY);
	}

	
	//glTexCoord3fv(p1.getNormal().getXLocation());
	
	glTexCoord2fv(t1.v);
	glNormal3fv(p1.getNormal().getXLocation());
	glVertex3fv(p1.getPosition().getXLocation());
	//Vector3f p;
	//p.getX()
	
	//glTexCoord3fv(p2.getNormal().getXLocation());
	glTexCoord2fv(t2.v);
	glNormal3fv(p2.getNormal().getXLocation());
	glVertex3fv(p2.getPosition().getXLocation());

	//glTexCoord3fv(p3.getNormal().getXLocation());
	glTexCoord2fv(t3.v);
	glNormal3fv(p3.getNormal().getXLocation());
	glVertex3fv(p3.getPosition().getXLocation());
	
}

void Cloth::setParticlePosition(int index, Particle p,float rad,float ang){
	Vector3f center5(40+20*cos(90*180/PI), -180, 25+20*sin(90*180/PI));
	center5.setX(rad * sin(ang*180/PI));
	center5.setZ(rad * cos(ang*180/PI));
	center5.setY(index*(-450)/(m_height-1));
	p.setPosition(center5);
}

// Check if the ball is intersecting the cloth
void Cloth::ballCollision(const Vector3f &center, const Vector3f &center2, const float radius,const float radius2){
	Vector3f center3(40+20*cos(0*180/PI), -8, 25+20*sin(0*180/PI));
	Vector3f center4(40+20*cos(45*180/PI), -20, 25+20*sin(45*180/PI));
	Vector3f center5(40+20*cos(90*180/PI), -180, 25+20*sin(90*180/PI));
	Vector3f center6(40+20*cos(135*180/PI), -30, 25+20*sin(135*180/PI));
	
	// Check each particle
	int num = (int)m_particles.size();
	#pragma omp parallel for
	
	/////////////////////////////////////////////
	///control cloth Points with yR Dimention////
	/////////////////////////////////////////////
	int i;
	for (i=0; i<m_height-1; i++)
	{
		center6.setX(0);
		center6.setZ(0);
		center6.setY(12*cos(0.01*collCounter+0.08*i*360/m_width));
		Particle* p = &m_particles[i*m_width+3];
		p->addForceAccumulated(p->getAcceleration() * (1 / p->getInverseMass())); 
		Vector3f force =p->getNormal() * (p->getNormal().dot(center5));
		p->addForceAccumulated(force);
		p->setNormal(Vector3f(0,0,0));
		
		/////////////
		///edge//////
		/////////////
		if(i%1==0){
			center5.setX(staticPointList[i] * sin(0*180/PI));
			center5.setZ(staticPointList[i] * cos(0*180/PI));
			center5.setY(i*(-750)/(m_height-1));
			m_particles[i*m_width].setPosition(center5);
			if(i>0)m_particles[i*m_width-1].setPosition(center5);
			
			center5.setX(staticPointList[i] * sin(-90*180/PI));
			center5.setZ(staticPointList[i] * cos(-90*180/PI));
			center5.setY(i*(-750)/(m_height-1));
			m_particles[i*m_width+7].setPosition(center5);

			center5.setX(staticPointList[i] * sin(90*180/PI));
			center5.setZ(staticPointList[i] * cos(90*180/PI));
			center5.setY(i*(-750)/(m_height-1));
			m_particles[i*m_width+(m_width-7)].setPosition(center5);

			//interactive Line
			center5.setX(radiusList[i] * sin(180*180/PI));
			center5.setZ(radiusList[i] * cos(180*180/PI));
			center5.setY(i*(-750)/(m_height-1)+yAdditionalList[i]);
			m_particles[i*m_width+modPointX].setPosition(center5);
			
		}
	}
	
	
	for (i=0; i<m_width; i++)
	{
		Vector3f v = m_particles[i].getPosition() - center;
		float l = v.lengthSquared();
		
		//////////////////////////////////////////////
		//Control Head Circle and Foot Circle/////////
		//////////////////////////////////////////////
		// Head /////////////////////////////////////
		center3.setX(offsetX+20*cos(360-0.018*i*360/m_width));
		center3.setZ(offsetZ+20*sin(360-0.018*i*360/m_width));
		m_particles[i].setPosition(center3.normalized() * radius + center3);
		m_particles[i].mulVelocity(0.1);
		/////////////////////////////////////// Head 
		// Foot /////////////////////////////////////
		float underRad;
		/////////////////////////////////////// Foot 

		
		// If inside the ball place it on the surface and dampen the velocity for friction
		/*if (l < radius*radius)
		{
			m_particles[i].setPosition(v.normalized() * radius + center);
			//m_particles[i].setPosition(v.normalized()*4 * radius + center);
			m_particles[i].mulVelocity(0.1);
		}*/
	}
	collCounter++;
	
	/// video ..:::: * + *   * . +
	bool bNewFrame = false;
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
	if (bNewFrame){
		acc_image.setFromPixels(vidPlayer.getPixels(), VIDEO_WIDTH, VIDEO_HEIGHT);
	}
}

// Draws the entire cloth
//void Cloth::draw() const{
void Cloth::draw() {
	
	//draw bugfollow
	glColor4f(1, 1, 1, 0);
	
	if (textureVidMode==1) {
		glColor4f(1, 1, 1, 0);
		acc_image.draw(0, 0);
		glColor4f(1, 1, 1, 1);
		acc_image.getTextureReference().bind();
	}else {
		clothTexture.grabScreen(0, 0, 800, 600);
		
		// Clear Screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glColor4f(1, 1, 1, 0);
		
		glColor4f(1, 1, 1, 1);
		clothTexture.getTextureReference().bind();
	}
	
	// For each quad draw the two triangles that compose it as they are not likely to be coplanar
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);
	
	blockX = img_width / m_width;
	blockY = img_height / m_height;
	
	for (int x = 0; x < m_width -1; ++x)
	//for (int x = 0; x < m_width/2 -1; ++x)
	{
		if(sideMode==0){
			if(x<modPointX || x>modPointX+m_width/2){
				for (int y =0; y < m_height-1; ++y)
				{
					Vector3f colour = ((x%4 < 2)^(y%4 < 2)) ? Vector3f(0.0f,0.0f,0.0f): Vector3f(1.0f, 1.0f, 1.0f);
					drawTriangle(*getProtectedParticle(x+1, y), *getProtectedParticle(x,y), *getProtectedParticle(x, y+1), colour,x,y,0);
					drawTriangle(*getProtectedParticle(x+1, y+1), *getProtectedParticle(x+1,y), *getProtectedParticle(x, y+1), colour,x,y,1);
				}
			}
		}else if(sideMode==1) {
			if(x>=modPointX && x<=modPointX+m_width/2){
				for (int y =0; y < m_height-1; ++y)
				{
					Vector3f colour = ((x%4 < 2)^(y%4 < 2)) ? Vector3f(0.0f,0.0f,0.0f): Vector3f(1.0f, 1.0f, 1.0f);
					drawTriangle(*getProtectedParticle(x+1, y), *getProtectedParticle(x,y), *getProtectedParticle(x, y+1), colour,x,y,0);
					drawTriangle(*getProtectedParticle(x+1, y+1), *getProtectedParticle(x+1,y), *getProtectedParticle(x, y+1), colour,x,y,1);
				}
			}
		}

			
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	if (textureVidMode==1) {
		acc_image.getTextureReference().unbind();
	}else {
		clothTexture.getTextureReference().unbind();
	}
}

// Step the cloth forward in time by the given duration
void Cloth::update(float duration) {
	int num = (int)m_particles.size();
	#pragma omp parallel for
	for (int i=0; i<num; ++i)
	{
		m_particles[i].integrate(duration*2);
	}
}

// Add force at one Point
void Cloth::addForceAtOnePoint(float forceScale, int x, int y){
	Particle* p;
	p = getParticle(x,y);				// Current particle
	float squares = 0;							// A count of the adjacent particles
	Vector3f springForce = Vector3f(0,0,0);		// Will contain the forces of all adjacent particles are applying
	float largestStretch = 20;					// Used to cap the length the cloth can stretch
/*
	// Evaluate the Closest 24 positions
	for (int a = -4; a <= 4; ++a) {
		for (int b = -4; b <= 4; ++b)
		{
			// Ensure a particle exist and it isn't the current one
			if ((a != 0 || b != 0) && (x+a >= 0) && (x+a < m_width) && (y+b >= 0) && (y+b < m_height))
			{
				// Get the direction this spring is pulling
				Vector3f springVector =  p->getPosition() - getProtectedParticle(x+a, y+b)->getPosition();
				//Vector3f springVector =  p->getPosition()*0.1;
				//Vector3f springVector = Vector3f(forceScale*p->getPosition().getX(), 0,forceScale*p->getPosition().getZ())*0.01;
				
				// Find how much force is exerted by this string
				float length = springVector.length();
				float normalLength = sqrt((a * m_distanceX) * (a * m_distanceX) + (b * m_distanceY) * (b * m_distanceY)) ;
				float forceScalar = (length - normalLength) / normalLength;
							
				// Add the force this particle is applying to the other particle forces
				springForce += springVector / length  * forceScalar * forceScale;
				squares++;
							
				// Keep track of which spring is exerting the most force
				if (forceScalar > largestStretch) {
					largestStretch = forceScalar;
				}
			} 
		}

		Vector3f springVector =  p->getPosition();
			
		Vector3f springForcApply = Vector3f(springForce.getX(),0,springForce.getZ());	
	// Apply the force of the cloth on this particle
		//p->addForceAccumulated(springForce / squares);
	//p->addForceAccumulated(springForcApply / squares);
	}
	*/
	
	Vector3f springVector2 =  p->getPosition();
	float length = springVector2.length();
	springVector2 = (springVector2/length)*forceScale*10.9;
	//Vector3f springForcApply = Vector3f(springVector2.getX(),springVector2.getY(),springVector2.getZ());
	Vector3f springForcApply = Vector3f(springVector2.getX(),0,springVector2.getZ());

	p->addForceAccumulated(springForcApply);
	
}


// Calculate the spring forces for clothlike behavior
void Cloth::calculateForces(const Vector3f &wind_dir, const Vector3f &ball_pos, const Vector3f &ball_pos2, const Vector3f &ball_pos3, float ball_radius){
	
	// Apply gravity, wind and reset the normals
	int num = (int)m_particles.size();
	#pragma omp parallel for
	for (int i=0; i<num; ++i)
	{
		Particle* p = &m_particles[i];
		// Alter the application	of gravity so it is not effected by mass
		p->addForceAccumulated(p->getAcceleration() * (1 / p->getInverseMass())); 
		
		// Apply the wind using the last calculated normals
		Vector3f force =p->getNormal() * (p->getNormal().dot(wind_dir));
		p->addForceAccumulated(force);

		// Reset the normal, will recalculate after position is adjusted
		p->setNormal(Vector3f(0,0,0));
	}

	ballCollision(ball_pos,ball_pos2,ball_radius,ball_radius);	// resolve collision with the ball
	calculateClothNormals();				// Calculate new normals

	// Calculate new forces
	for (int x = 0; x < m_width; ++x) {
		for (int y =0; y < m_height; ++y)
		{
			Particle* p = getParticle(x,y);				// Current particle
			float squares = 0;							// A count of the adjacent particles
			Vector3f springForce = Vector3f(0,0,0);		// Will contain the forces of all adjacent particles are applying
			float largestStretch = 0;					// Used to cap the length the cloth can stretch

			// Evaluate the Closest 24 positions
			for (int a = -2; a <= 2; ++a) {
				for (int b = -2; b <= 2; ++b)
				{
					// Ensure a particle exist and it isn't the current one
					if ((a != 0 || b != 0) && (x+a >= 0) && (x+a < m_width) && (y+b >= 0) && (y+b < m_height))
					{
						// Get the direction this spring is pulling
						Vector3f springVector = getProtectedParticle(x+a, y+b)->getPosition() - p->getPosition();

						// Find how much force is exerted by this string
						float length = springVector.length();
						float normalLength = sqrt((a * m_distanceX) * (a * m_distanceX) + (b * m_distanceY) * (b * m_distanceY)) ;
						float forceScalar = (length - normalLength) / normalLength;

						// Add the force this particle is applying to the other particle forces
						springForce += springVector / length  * forceScalar;
						squares++;

						// Keep track of which spring is exerting the most force
						if (forceScalar > largestStretch) {
							largestStretch = forceScalar;
						}
					} 
				}
			}

			// If a spring is stretched beyond 20% we will begin to minimize the effects of other forces to maintain the cloth shape
			/*if (largestStretch >= 0.25){
				p->mulForceAccumulated((largestStretch >=0.75)? 0 : (0.75-largestStretch));
			}*/

			// Apply the force of the cloth on this particle
			p->addForceAccumulated(springForce / squares);
		}
	}
	
}

void Cloth::inverceMathAdd(int i){
	for (int x = 0; x < m_width; ++x) {
		for (int y =0; y < m_height; ++y)
		{
			Particle* p = getParticle(x,y);
			int tmpInverce = p->getInverseMass();
			if(tmpInverce==1)tmpInverce=2;
			if(tmpInverce==4)tmpInverce=3;
			p->setInverseMass(tmpInverce+i);
		}
	}
}

void Cloth::dampingAdd(int i){
	for (int x = 0; x < m_width; ++x) {
		for (int y =0; y < m_height; ++y)
		{
			Particle* p = getParticle(x,y);
			int tmpInverce = p->getDamping();
			p->setDamping(tmpInverce+i);
		}
	}
}
void Cloth::positionAdd(int i){
	modParam += i;
}
void Cloth::plotRadiusList(){
	int i;
	for(i=0; i<radiusList.size();i++){
		printf("%f,", radiusList[i]);
	}
	printf("\n-------------\n");
}

void Cloth::updateWithSounds(float *sounds){
	if (collCounter<240) {
		return;
	}
	
	if(collCounter%1==0){		
	
		int i,j;
		int counter=0;
			for	(i=4;i<m_width;i++){
				for(j=4;j<m_height;j++){
					addForceAtOnePoint(sounds[int(counter%512)]*0.06, i, j);
					counter++;
				}
			}
	
	}
}
