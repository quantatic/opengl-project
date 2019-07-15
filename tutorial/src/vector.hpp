#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

class vec3 {
	float x;
	float y;
	float z;

	public:
		vec3();
		vec3(float x, float y, float z);
		vec3(const vec3 &other);
		vec3 &operator=(const vec3 &other);

		vec3 &operator+=(const vec3 &other);
		vec3 operator+(const vec3 &other) const; 

		vec3 &operator-=(const vec3 &other);
		vec3 operator-(const vec3 &other) const; 

		vec3 &operator*=(float other); 
		vec3 operator*(float other) const; 

		vec3 &operator/=(float other); 
		vec3 operator/(float other) const; 

		vec3 cross(const vec3 &other) const;
		float dot(const vec3 &other) const; 

		vec3 normal() const;

		float getX() const;
		float getY() const;
		float getZ() const;

		friend std::ostream &operator<<(std::ostream &lhs, const vec3 &rhs);

		~vec3();
};

#endif
