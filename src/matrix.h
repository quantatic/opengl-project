#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat4 {
    float vals[16];
} mat4;

mat4 rotationMatrix(float x, float y, float z, float angle);

float *matrixPointer(mat4 *in);

#endif
