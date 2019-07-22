#include "vector.hpp"

#include <iostream>

#include <cmath>

Vec3::Vec3() :
	x(0),
	y(0),
	z(0)
{ };

Vec3::Vec3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{ };

Vec3::Vec3(const Vec3 &other) :
	x(other.x),
	y(other.y),
	z(other.z)
{ };

Vec3 &Vec3::operator=(const Vec3 &other) {
	if(this != &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}

	return *this;
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 Vec3::operator+(const Vec3 &other) const {		
	Vec3 tmp(*this);
	tmp += other;
	return tmp;
}

Vec3 &Vec3::operator-=(const Vec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 Vec3::operator-(const Vec3 &other) const {
	Vec3 tmp(*this);
	tmp -= other;
	return tmp;
}

Vec3 &Vec3::operator*=(float other) {
	x *= other;
	y *= other;
	z *= other;

	return *this;
}	

Vec3 Vec3::operator*(float other) const {
	Vec3 tmp(*this);
	tmp *= other;
	return tmp;
}

Vec3 &Vec3::operator/=(float other) {
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

Vec3 Vec3::operator/(float other) const {
	Vec3 tmp(*this);
	tmp /= other;
	return tmp;
}


Vec3 Vec3::cross(const Vec3 &other) const {
	float resX = y * other.z - z * other.y;
	float resY = z * other.x - x * other.z;
	float resZ = x * other.y - y * other.x;

	return Vec3(resX, resY, resZ);
}

float Vec3::dot(const Vec3 &other) const {
	return (x * other.x) + (y * other.y) + (z * other.z);
}

float Vec3::getX() const {
	return x;
}

float Vec3::getY() const {
	return y;
}

float Vec3::getZ() const {
	return z;
}

Vec3 Vec3::normal() const {
	float magnitude = sqrt(x * x + y * y + z * z);

	return Vec3(x / magnitude, y / magnitude, z / magnitude);
}

std::ostream &operator<<(std::ostream &lhs, const Vec3 &rhs) {
	lhs << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";
	return lhs;
}

Vec3::~Vec3() { }
