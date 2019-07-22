#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class Vec3 {
	float x;
	float y;
	float z;

	public:
		Vec3();
		Vec3(float x, float y, float z);
		Vec3(const Vec3 &other);
		Vec3 &operator=(const Vec3 &other);

		Vec3 &operator+=(const Vec3 &other);
		Vec3 operator+(const Vec3 &other) const; 

		Vec3 &operator-=(const Vec3 &other);
		Vec3 operator-(const Vec3 &other) const; 

		Vec3 &operator*=(float other); 
		Vec3 operator*(float other) const; 

		Vec3 &operator/=(float other); 
		Vec3 operator/(float other) const; 

		Vec3 cross(const Vec3 &other) const;
		float dot(const Vec3 &other) const; 

		Vec3 normal() const;

		float getX() const;
		float getY() const;
		float getZ() const;

		friend std::ostream &operator<<(std::ostream &lhs, const Vec3 &rhs);

		~Vec3();
};

#endif
