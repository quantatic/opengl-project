#include "matrix.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct mat4 {
    float vals[16];
} mat4;

mat4 *identityMatrix() {
    mat4 *result = malloc(sizeof(mat4));

    for(int i = 0; i < 16; i++) {
        result->vals[i] = 0;
    }

    result->vals[0] = 1;
    result->vals[5] = 1;
    result->vals[10] = 1;
    result->vals[15] = 1;

    return result;
}

void rotateMatrix(mat4 *result, mat4 *in, float x, float y, float z, float angle) {
    float scale = sqrt(x * x + y * y + z * z); //up vector has to be unit vector
    float unitX = x / scale;
    float unitY = y / scale;
    float unitZ = z / scale;

    mat4 rotation; //stores the rotation matrix used
	rotation.vals[0] = cos(angle) + unitX * unitX * (1 - cos(angle));
	rotation.vals[1] = unitX * unitY * (1 - cos(angle)) + unitZ * sin(angle);
	rotation.vals[2] = unitZ * unitX * (1 - cos(angle)) - unitY * sin(angle);
	rotation.vals[3] = 0;

	rotation.vals[4] = unitX * unitY * (1 - cos(angle)) - unitZ * sin(angle);
	rotation.vals[5] = cos(angle) + unitY * unitY * (1 - cos(angle));
	rotation.vals[6] = unitZ * unitY * (1 - cos(angle)) + unitX * sin(angle);
	rotation.vals[7] = 0;

	rotation.vals[8] = unitX * unitZ * (1 - cos(angle)) + unitY * sin(angle);
	rotation.vals[9] = unitY * unitZ * (1 - cos(angle)) - unitX * sin(angle);
	rotation.vals[10] = cos(angle) + unitZ * unitZ * (1 - cos(angle));
	rotation.vals[11] = 0;

	rotation.vals[12] = 0;
	rotation.vals[13] = 0;
	rotation.vals[14] = 0;
	rotation.vals[15] = 1;

    multiplyMatrices(result, &rotation, in);
}

void scaleMatrix(mat4 *result, mat4 *in, float scaleX, float scaleY, float scaleZ) {
    mat4 scale; //stores the scale matrix used;
    
    for(int i = 0; i < 16; i++) {
        scale.vals[i] = 0;
    }

    scale.vals[0] = scaleX;
    scale.vals[5] = scaleY;
    scale.vals[10] = scaleZ;
    scale.vals[15] = 1;

    multiplyMatrices(result, &scale, in);
}

void translateMatrix(mat4 *result, mat4 *in, float translateX, float translateY, float translateZ) {
    mat4 translation; //stores the translation matrix used

    for(int i = 0; i < 16; i++) {
        translation.vals[i] = 0;
    }

    translation.vals[0] = 1;            //set up diagonals
    translation.vals[5] = 1;
    translation.vals[10] = 1;
    translation.vals[15] = 1;

    translation.vals[12] = translateX;  //set up actual translation values
    translation.vals[13] = translateY;
    translation.vals[14] = translateZ;

    multiplyMatrices(result, &translation, in);
}

void multiplyMatrices(mat4 *result, mat4 *a, mat4 *b) {
    float tmp[16]; //temporary holder for results, enable same input and output matrix

    for(int c = 0; c < 4; c++) {
        for(int r = 0; r < 4; r++) {
            float total = 0;
            int index = c * 4 + r;

            for(int i = 0; i < 4; i++) {
                int p = i * 4 + r;
                int q = c * 4 + i;

                total += a->vals[p] * b->vals[q];
            }

            tmp[index] = total;
        }
    }
    
    for(int i = 0; i < 16; i++) { //copy from tmp results to actual results
        result->vals[i] = tmp[i];
    }

}

float *matrixPointer(mat4 *in) {
	return in->vals;
}

void destroyMatrix(mat4 *mat) {
    free(mat);
}

void printMatrix(mat4 *in) {
    printf("[");

    for(int r = 0; r < 4; r++) {
        printf("\n\t");
        for(int c = 0; c < 4; c++) {
            int index = c * 4 + r;

            printf("%f ", in->vals[index]);
        }

        printf("\n");
    }

    printf("]\n");
}
