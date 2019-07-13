#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

#include <GL/glew.h>

typedef struct mat4 {
    float vals[16];
} mat4;

void identityMatrix(mat4 *result);

//result and in matrix can be the same
void rotateMatrix(mat4 *result, mat4 *in, vec3 *axis, float angle);

//result and in matrix can be the same
void scaleMatrix(mat4 *result, mat4 *in, vec3 *scale);

//result and in matrix can be the same
void translateMatrix(mat4 *result, mat4 *in, vec3 *translation);

void orthoMatriz(mat4 *result, float left, float right, float bottom, float top, float near, float far);
void perspectiveMatrix(mat4 *result, float fov, float aspect, float near, float far);

//result and input matrices can be the same
void multiplyMatrices(mat4 *result, mat4 *a, mat4 *b);

//copies matrix data, so matrix variable safe to delete right after call
void setUniformMatrix(GLuint program, char *name, mat4 *in);

void destroyMatrix(mat4 *mat);

void printMatrix(mat4 *in);

#endif
