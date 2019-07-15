#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

#include <GL/glew.h>

#include <cmath>
#include <iostream>

class mat4 {
	float vals[16];

	public:
		mat4();
		mat4(float diagonal);
		mat4(const mat4 &other);
		mat4 &operator=(const mat4 &other);

		static mat4 rotationMatrix(const vec3 &axis, float angle);
		static mat4 scaleMatrix(const vec3 &scale);
		static mat4 translationMatrix(const vec3 &translation);
		static mat4 orthoMatrix(float left, float right, float bottom, float top, float near, float far);
		static mat4 fulstrumMatrix(float left, float right, float bottom, float top, float near, float far);
		static mat4 perspectiveMatrix(float fov, float aspect, float near, float far);
		static mat4 lookAt(const vec3 &cameraPos, const vec3 &targetPos, const vec3 &upVector);

		mat4 &operator+=(const mat4 &other);
		mat4 operator+(const mat4 &other) const;

		mat4 &operator-=(const mat4 &other);
		mat4 operator-(const mat4 &other) const;

		mat4 &operator*=(const mat4 &other);
		mat4 operator*(const mat4 &other) const;

		void setUniformMatrix(GLuint program, const char *name) const;

		friend std::ostream &operator<<(std::ostream &lhs, const mat4 &rhs);		
		~mat4();
};


#endif
