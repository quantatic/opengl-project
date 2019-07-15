#include "vector.hpp"

#include <iostream>

#include <cmath>

vec3::vec3() :
	x(0),
	y(0),
	z(0)
{ };

vec3::vec3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{ };

vec3::vec3(const vec3 &other) :
	x(other.x),
	y(other.y),
	z(other.z)
{ };

vec3 &vec3::operator=(const vec3 &other) {
	if(this != &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}

	return *this;
}

vec3 &vec3::operator+=(const vec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vec3 vec3::operator+(const vec3 &other) const {		
	vec3 tmp(*this);
	tmp += other;
	return tmp;
}

vec3 &vec3::operator-=(const vec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vec3 vec3::operator-(const vec3 &other) const {
	vec3 tmp(*this);
	tmp -= other;
	return tmp;
}

vec3 &vec3::operator*=(float other) {
	x *= other;
	y *= other;
	z *= other;

	return *this;
}	

vec3 vec3::operator*(float other) const {
	vec3 tmp(*this);
	tmp *= other;
	return tmp;
}

vec3 &vec3::operator/=(float other) {
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

vec3 vec3::operator/(float other) const {
	vec3 tmp(*this);
	tmp /= other;
	return tmp;
}


vec3 vec3::cross(const vec3 &other) const {
	float resX = y * other.z - z * other.y;
	float resY = z * other.x - x * other.z;
	float resZ = x * other.y - y * other.x;

	return vec3(resX, resY, resZ);
}

float vec3::dot(const vec3 &other) const {
	return (x * other.x) + (y * other.y) + (z * other.z);
}

float vec3::getX() const {
	return x;
}

float vec3::getY() const {
	return y;
}

float vec3::getZ() const {
	return z;
}

vec3 vec3::normal() const {
	float magnitude = sqrt(x * x + y * y + z * z);

	return vec3(x / magnitude, y / magnitude, z / magnitude);
}

std::ostream &operator<<(std::ostream &lhs, const vec3 &rhs) {
	lhs << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
	return lhs;
}

vec3::~vec3() { }
