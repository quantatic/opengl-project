#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "vector.hpp"

#include <GL/glew.h>

#include <cmath>
#include <iostream>

class Mat4 {
	float vals[16];

	public:
		Mat4();
		Mat4(float diagonal);
		Mat4(const Mat4 &other);
		Mat4 &operator=(const Mat4 &other);

		static Mat4 rotationMatrix(const Vec3 &axis, float angle);
		static Mat4 scaleMatrix(const Vec3 &scale);
		static Mat4 translationMatrix(const Vec3 &translation);
		static Mat4 orthoMatrix(float left, float right, float bottom, float top, float near, float far);
		static Mat4 fulstrumMatrix(float left, float right, float bottom, float top, float near, float far);
		static Mat4 perspectiveMatrix(float fov, float aspect, float near, float far);
		static Mat4 lookAt(const Vec3 &cameraPos, const Vec3 &targetPos, const Vec3 &upVector);

		Mat4 &operator+=(const Mat4 &other);
		Mat4 operator+(const Mat4 &other) const;

		Mat4 &operator-=(const Mat4 &other);
		Mat4 operator-(const Mat4 &other) const;

		Mat4 &operator*=(const Mat4 &other);
		Mat4 operator*(const Mat4 &other) const;

		void setUniformMatrix(GLuint program, const char *name) const;

		friend std::ostream &operator<<(std::ostream &lhs, const Mat4 &rhs);		
		~Mat4();
};


#endif
