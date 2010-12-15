#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3f.h"
#include <math.h>

// Simple particle class which will compose the cloth
class Particle 
{
private:
	Vector3f m_position;			// Current Location of the particle
	Vector3f m_velocity;			// Direction and speed the particle is traveling in
	Vector3f m_acceleration;		// Speed at which the particle is accelerating (used for gravity)
	Vector3f m_forceAccumulated;	// Force that has been accumulated since the last update
	Vector3f m_normal;				// Normal of this Particle, used to light the cloth when drawing
	float m_damping;				// Amount of velocity lost per update
	float m_inverseMass;			// Inverse of the weight (since the value is 1 this is effectively not used)
	bool m_stationary;				// Whether this particle is currently capible of movement
	
public:
	int xIndex;
	int yIndex;
	// Copy Assignment Operator
	Particle& operator= (const Particle& particle);

	// Constructors
	Particle(Vector3f position, Vector3f acceleration);
	Particle(const Particle& particle);
	Particle();

	// Move the Particle forward in time by applying acceleration to the velocity and moving the position by the velocity
	void integrate(float duration);

	// Accessor functions
	inline Vector3f getPosition() const {return m_position;}
	inline Vector3f getVelocity() const {return m_velocity;}
	inline Vector3f getAcceleration() const {return m_acceleration;}
	inline Vector3f getForceAccumulated() const {return m_forceAccumulated;}
	inline Vector3f getNormal() const {return m_normal;}
	inline float getDamping() const {return m_damping;}
	inline float getInverseMass() const {return m_inverseMass;}
	inline bool getStationary() const {return m_stationary;}

	inline void addNormal(const Vector3f& normal) {m_normal += normal;}
	inline void addForceAccumulated(const Vector3f& forceAccumulated) {m_forceAccumulated += forceAccumulated;}
	inline void mulVelocity(const float scalar) {m_velocity *= scalar;}
	inline void mulForceAccumulated(const float scalar) {m_forceAccumulated *= scalar;}

	inline void setPosition(const Vector3f& position) {m_position = position;}
	inline void setPositionXZ(const Vector3f& position) {
		float tempY = m_position.getY();
		m_position = position;
		m_position.setY(tempY);
	}
	inline void setVelocity(const Vector3f& velocity) {m_velocity = velocity;}
	inline void setAcceleration(const Vector3f& acceleration) {m_acceleration = acceleration;}
	inline void setForceAccumulated(const Vector3f& forceAccumulated) {m_forceAccumulated = forceAccumulated;}
	inline void setNormal(const Vector3f& normal) {m_normal = normal;}
	inline void setDamping(const float damping) {m_damping = damping;}
	inline void setInverseMass(const float inverseMass) {m_inverseMass = inverseMass;}
	inline void setStationary(const bool stationary) {m_stationary = stationary;}
};

#endif
