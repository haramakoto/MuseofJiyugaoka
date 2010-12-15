#include "Vector3f.h"

// Constructors
Vector3f::Vector3f(float x, float y, float z) 
 : m_x(x), m_y(y), m_z(z)
{
}

Vector3f::Vector3f(const Vector3f& vector) 
 : m_x(vector.getProtectedX()), m_y(vector.getProtectedY()), m_z(vector.getProtectedZ())
{
}

Vector3f::Vector3f() 
 : m_x(0), m_y(0), m_z(0)
{
}

// Calculate the length of the vector
float Vector3f::length() const{
	return sqrt(m_x*m_x+m_y*m_y+m_z*m_z);
}

// Calculate the squared length of the vector
float Vector3f::lengthSquared() const{
	return m_x*m_x+m_y*m_y+m_z*m_z;
}

// Create a unit length vector in this vector's direction
Vector3f Vector3f::normalized() const{
	float l = length();
	return Vector3f(m_x / l, m_y/l, m_z/l);
}

// Add a vector to this one
void Vector3f::operator += (const Vector3f &vector){
	m_x += vector.getProtectedX();
	m_y += vector.getProtectedY();
	m_z += vector.getProtectedZ();
}

// Subtract a vector from this one
void Vector3f::operator-= (const Vector3f &vector){
	m_x -= vector.getProtectedX();
	m_y -= vector.getProtectedY();
	m_z -= vector.getProtectedZ();
}

// Multiply this vector by a scalar amount
void Vector3f::operator*= (const float &scalar){
	m_x*=scalar; 
	m_y*=scalar; 
	m_z*=scalar;
}

// Divide this vector by a scalar amount
void Vector3f::operator/= (const float &scalar){
	m_x/=scalar; 
	m_y/=scalar; 
	m_z/=scalar;
}

// Divide the vector by a given scalar amount
Vector3f Vector3f::operator/ (const float &scalar) const{
	return Vector3f(m_x/scalar, m_y/scalar, m_z/scalar);
}

// Subtract two vectors
Vector3f Vector3f::operator- (const Vector3f &vector) const{
	return Vector3f(m_x-vector.getProtectedX(), m_y-vector.getProtectedY(), m_z-vector.getProtectedZ());
}

// Add two vectors
Vector3f Vector3f::operator+ (const Vector3f &vector) const{
	return Vector3f(m_x+vector.getProtectedX(), m_y+vector.getProtectedY(), m_z+vector.getProtectedZ());
}

// Multiply a vector by a scalar amount
Vector3f Vector3f::operator* (const float &scalar) const{
	return Vector3f(m_x*scalar, m_y*scalar, m_z*scalar);
}

// Invert a vector
Vector3f Vector3f::operator- () const{
	return Vector3f(-m_x, -m_y, -m_z);
}

// Find the cross product of this vector and another
Vector3f Vector3f::cross(const Vector3f &vector) const{
	return Vector3f(m_y*vector.getProtectedZ() - m_z*vector.getProtectedY(), m_z*vector.getProtectedX() - m_x*vector.getProtectedZ(), m_x*vector.getProtectedY() - m_y*vector.getProtectedX());
}

// Find the dot product of this vector and another
float Vector3f::dot(const Vector3f &vector) const{
	return m_x*vector.getProtectedX() + m_y*vector.getProtectedY() + m_z*vector.getProtectedZ();
}