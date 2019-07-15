#include "matrix.hpp"

mat4::mat4() {
	for(int i = 0; i < 16; i++) {
		vals[i] = 0;
	}
}

mat4::mat4(float diagonal) {
	for(int i = 0; i < 16; i++) {
		vals[i] = 0;
	}

	vals[0] = diagonal;
	vals[5] = diagonal;
	vals[10] = diagonal;
	vals[15] = diagonal;
}

mat4::mat4(const mat4 &other) {
	for(int i = 0; i < 16; i++) {
		vals[i] = other.vals[i];
	}
}

mat4 &mat4::operator=(const mat4 &other) {
	if(this != &other) {
		for(int i = 0; i < 16; i++) {
			vals[i] = other.vals[i];
		}
	}

	return *this;
}

mat4 mat4::rotationMatrix(const vec3 &axis, float angle) {
	mat4 result;

	vec3 normalized = axis.normal();

	result.vals[0] = cos(angle) + normalized.getX() * normalized.getX() * (1 - cos(angle));
	result.vals[1] = normalized.getX() * normalized.getY() * (1 - cos(angle)) + normalized.getZ() * sin(angle);
	result.vals[2] = normalized.getZ() * normalized.getX() * (1 - cos(angle)) - normalized.getY() * sin(angle);
	result.vals[3] = 0;

	result.vals[4] = normalized.getX() * normalized.getY() * (1 - cos(angle)) - normalized.getZ() * sin(angle);
	result.vals[5] = cos(angle) + normalized.getY() * normalized.getY() * (1 - cos(angle));
	result.vals[6] = normalized.getZ() * normalized.getY() * (1 - cos(angle)) + normalized.getX() * sin(angle);
	result.vals[7] = 0;

	result.vals[8] = normalized.getX() * normalized.getZ() * (1 - cos(angle)) + normalized.getY() * sin(angle);
	result.vals[9] = normalized.getY() * normalized.getZ() * (1 - cos(angle)) - normalized.getX() * sin(angle);
	result.vals[10] = cos(angle) + normalized.getZ() * normalized.getZ() * (1 - cos(angle));
	result.vals[11] = 0;

	result.vals[12] = 0;
	result.vals[13] = 0;
	result.vals[14] = 0;
	result.vals[15] = 1;

	return result;
}

mat4 mat4::scaleMatrix(const vec3 &scale) {
	mat4 result(1);

	result.vals[0] = scale.getX();
	result.vals[5] = scale.getY();
	result.vals[10] = scale.getZ();
	result.vals[15] = 1;

	return result;
}

mat4 mat4::translationMatrix(const vec3 &translation) {
	mat4 result(1);

	result.vals[12] = translation.getX();
	result.vals[13] = translation.getY();
	result.vals[14] = translation.getZ();

	return result;
}

mat4 mat4::orthoMatrix(float left, float right, float bottom, float top, float near, float far) {
	mat4 result;

    result.vals[0] = 2 / (right - left);

    result.vals[5] = 2 / (top - bottom);

    result.vals[10] = 2 / (near - far);

    result.vals[12] = (right + left) / (left - right);
    result.vals[13] = (top + bottom) / (bottom - top);
    result.vals[14] = (far + near) / (near - far);
    result.vals[15] = 1;

	return result;
}

mat4 mat4::fulstrumMatrix(float left, float right, float bottom, float top, float near, float far) {
	mat4 result;

    result.vals[0] = 2 * near / (right - left);

    result.vals[5] = 2 * near / (top - bottom);

    result.vals[8] = (right + left) / (right - left);
    result.vals[9] = (top + bottom) / (top - bottom);
    result.vals[10] = (far + near) / (near - far);
    result.vals[11] = -1;

    result.vals[14] = 2 * far * near / (near - far);

	return result;
}

mat4 mat4::perspectiveMatrix(float fov, float aspect, float near, float far) {
    float top = near * tan(M_PI / 180 * fov / 2);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    return fulstrumMatrix(left, right, bottom, top, near, far);
}

mat4 mat4::lookAt(const vec3 &cameraPos, const vec3 &targetPos, const vec3 &upVector) {
	vec3 cameraDirectionNormalized = (cameraPos - targetPos).normal();
	vec3 upVectorNormalized = upVector.normal();
	vec3 cameraRightNormalized = upVectorNormalized.cross(cameraDirectionNormalized);

	vec3 cameraUpNormalized = cameraDirectionNormalized.cross(cameraRightNormalized).normal();

	mat4 coordinateTransformation;
	coordinateTransformation.vals[0] = cameraRightNormalized.getX();
	coordinateTransformation.vals[1] = cameraUpNormalized.getX();
	coordinateTransformation.vals[2] = cameraDirectionNormalized.getX();
	coordinateTransformation.vals[3] = 0;

	coordinateTransformation.vals[4] = cameraRightNormalized.getY();
	coordinateTransformation.vals[5] = cameraUpNormalized.getY();
	coordinateTransformation.vals[6] = cameraDirectionNormalized.getY();
	coordinateTransformation.vals[7] = 0;

	coordinateTransformation.vals[8] = cameraRightNormalized.getZ();
	coordinateTransformation.vals[9] = cameraUpNormalized.getZ();
	coordinateTransformation.vals[10] = cameraDirectionNormalized.getZ();
	coordinateTransformation.vals[11] = 0;

	coordinateTransformation.vals[12] = 0;
	coordinateTransformation.vals[13] = 0;
	coordinateTransformation.vals[14] = 0;
	coordinateTransformation.vals[15] = 1;

    mat4 coordinateTranslation(1);
    
    coordinateTranslation.vals[12] = -cameraPos.getX();
    coordinateTranslation.vals[13] = -cameraPos.getY();
    coordinateTranslation.vals[14] = -cameraPos.getZ();

	return coordinateTransformation * coordinateTranslation;
}

mat4 &mat4::operator+=(const mat4 &other) {
	for(int i = 0; i < 16; i++) {
		vals[i] += other.vals[i];
	}

	return *this;
}

mat4 mat4::operator+(const mat4 &other) const {
	mat4 tmp(*this);
	tmp += other;
	return tmp;
}

mat4 &mat4::operator-=(const mat4 &other) {
	for(int i = 0; i < 16; i++) {
		vals[i] -= other.vals[i];
	}

	return *this;
}

mat4 mat4::operator-(const mat4 &other) const {
	mat4 tmp(*this);
	tmp -= other;
	return tmp;
}

mat4 &mat4::operator*=(const mat4 &other) {
	*this = *this * other;
	return *this;
}

mat4 mat4::operator*(const mat4 &other) const {
	mat4 result;

	for(int c = 0; c < 4; c++) {
		for(int r = 0; r < 4; r++) {
			float total = 0;
			int index = c * 4 + r;

			for(int i = 0; i < 4; i++) {
				int p = i * 4 + r;
				int q = c * 4 + i;

				total += vals[p] * other.vals[q];
			}
			
			result.vals[index] = total;
		}
	}

	return result;
}

void mat4::setUniformMatrix(GLuint program, const char *name) const {
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, vals);
}

std::ostream &operator<<(std::ostream &lhs, const mat4 &rhs) {
	lhs << "[";

	for(int r = 0; r < 4; r++) {
		lhs << "\n\t";
		for(int c = 0; c < 4; c++) {
			int index = c * 4 + r;

			lhs << rhs.vals[index] << " ";
		}

		lhs << "\n";
	}

	lhs << "]\n";

	return lhs;
}

mat4::~mat4() { };
