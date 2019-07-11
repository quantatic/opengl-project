#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat4 mat4; //opaque pointer definition

mat4 *identityMatrix();

//result and in matrix can be the same
void rotateMatrix(mat4 *result, mat4 *in, float x, float y, float z, float angle);

//result and in matrix can be the same
void scaleMatrix(mat4 *result, mat4 *in, float scaleX, float scaleY, float scaleZ);

//result and in matrix can be the same
void translateMatrix(mat4 *result, mat4 *in, float translateX, float translateY, float translateZ);

//result and input matrices can be the same
void multiplyMatrices(mat4 *result, mat4 *a, mat4 *b);

//values returned column major
float *matrixPointer(mat4 *in);

void destroyMatrix(mat4 *mat);

void printMatrix(mat4 *in);

#endif
