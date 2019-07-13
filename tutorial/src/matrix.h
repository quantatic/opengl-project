#ifndef MATRIX_H
#define MATRIX_H

#include <GL/glew.h>

typedef struct mat4 {
    float vals[16];
} mat4;

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

////////////////////////////////////////////////////////////////////////////////

void initializeIdentityMatrix(mat4 *result);

//result and in matrix can be the same
void rotateMatrix(mat4 *result, mat4 *in, vec3 *axis, float angle);

//result and in matrix can be the same
void scaleMatrix(mat4 *result, mat4 *in, vec3 *scale);

//result and in matrix can be the same
void translateMatrix(mat4 *result, mat4 *in, vec3 *translation);

void orthoMatrix(mat4 *result, float left, float right, float bottom, float top, float near, float far);
void perspectiveMatrix(mat4 *result, float fov, float aspect, float near, float far);
void lookAt(mat4 *result, vec3 *cameraPos, vec3 *targetPos, vec3 *upVector);

//result and input matrices can be the same
void multiplyMatrices(mat4 *result, mat4 *a, mat4 *b);

//copies matrix data, so matrix variable safe to delete right after call
void setUniformMatrix(GLuint program, char *name, mat4 *in);

void destroyMatrix(mat4 *mat);

void printMatrix(mat4 *in);

////////////////////////////////////////////////////////////////////////////////

void initializeVector(vec3 *result, float x, float y, float z);

void destroyVector(vec3 *in);

//result can be the same as input
void crossProduct(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void normal(vec3 *result, vec3 *in);

//result can be the same as input
void addVectors(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void subtractVectors(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void multiplyVectors(vec3 *result, vec3 *a, float scalar);

//result can be the same as input
void divideVectors(vec3 *result, vec3 *a, float scalar);

void printVector(vec3 *in);

#endif
