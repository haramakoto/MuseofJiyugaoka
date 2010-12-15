#ifndef CLOTH_H
#define CLOTH_H

#include "Particle.h"
#include <vector>
//#include <gl/glut.h>

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVectorMath.h"

// Class that contains the cloth object
class Cloth 
{
private: 
	float m_dimensionWidth;				// Width of the cloth
	float m_dimensionHeight;			// Height of the cloth
	float m_distanceX;					// Width between particles
	float m_distanceY;					// Height between particles
	int m_width;						// Number of particles contained in the width
	int m_height;						// Number of particles contained in the height
	int m_bpp;
	int img_width;						// Number of particles contained in the width
	int img_height;						// Number of particles contained in the height
	int collCounter;
	
	// about texture ----------------------------------------
	int textureVidMode;
	int textureIndex;
	
	std::vector<Particle> m_particles;	// Contains all the particles of the cloth
	
	ofImage clothTexture;
	ofTexture myTexture;
	ofTextureData myTextureData;
	ofxCvColorImage	acc_image;
	
	//modify parameter
	int modParam;
	
	// Calculates the normals of all the particles
	void calculateClothNormals();

	// Gets a particle from the particle array
	Particle* getParticle(int x, int y);
	
//	const Particle* Cloth::getProtectedParticle(int x, int y) const;
	const Particle* getProtectedParticle(int x, int y) const;

	// Draws a triangle of the cloth
	static void drawTriangle(const Particle& p1, const Particle& p2, const Particle& p3, const Vector3f& color, int x, int y, int isFront);

	// Used to find normals of a triangle
	static Vector3f calculateTriangleCross(const Particle &p1, const Particle &p2, const Particle &p3);

	// Check if the ball is intersecting the cloth
	void ballCollision(const Vector3f &center, const Vector3f &center2, const float radius, const float radius2);
public: 
	// Constructor
	Cloth(float width, float height, int particles_in_width, int particles_in_height);

	// Draws the entire cloth
	//void draw() const;
	void draw();

	// Step the cloth forward in time by the given duration
	void update(float duration);

	// Calculate the spring forces for clothlike behavior
	void calculateForces(const Vector3f &wind_dir, const Vector3f &ball_pos, const Vector3f &ball_pos2, const Vector3f &ball_pos3, float ball_radius);
	
	void addForceAtOnePoint(float forceScale, int x, int y);
	
	void setUpCloth();
	void imageTextureSetup(string url);
	void videoTextureSetup(string url);
	void updateWithSounds(float *sounds);
	void textureChange(int i);
	void inverceMathAdd(int i);
	void dampingAdd(int i);
	void positionAdd(int i);
	void setParticlePosition(int index, Particle p,float rad,float ang);
	
	// set Modifiable Point Index //////////////////////
	int modifyIndex;
	void setModiablePointIndex(int i);
	//modify Radius at Point
	void modRadiusAtPoint(float s);
	void modYAtPoint(float s);
	void plotRadiusList();
	
	int counterX,counterY;
	float offsetX, offsetZ;
	int editableX;	//Number of Editable Point X
	int editableY;	//Number of Editable Point Y
	int sideMode;
	std::vector<float> radiusList;
	std::vector<float> yAdditionalList;
};

#endif