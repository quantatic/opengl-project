#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <GL/glew.h>

typedef struct mat4 mat4; //opaque pointer definition

mat4 *identityMatrix();

//result and in matrix can be the same
void rotateMatrix(mat4 *result, mat4 *in, vec3 axis, float angle);

//result and in matrix can be the same
void scaleMatrix(mat4 *result, mat4 *in, vec3 scale);

//result and in matrix can be the same
void translateMatrix(mat4 *result, mat4 *in, vec3 direction);

mat4 *orthoMatrix(float left, float right, float bottom, float top, float near, float far);
mat4 *perspectiveMatrix(float fov, float aspect, float near, float far);

//result and input matrices can be the same
void multiplyMatrices(mat4 *result, mat4 *a, mat4 *b);

void setUniformMatrix(GLuint program, char *name, mat4 *in);

//values returned column major
float *matrixPointer(mat4 *in);

void destroyMatrix(mat4 *mat);

void printMatrix(mat4 *in);

#endif
