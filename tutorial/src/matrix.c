#include "matrix.h"

#include <GL/glew.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void identityMatrix(mat4 *result) {

    for(int i = 0; i < 16; i++) {
        result->vals[i] = 0;
    }

    result->vals[0] = 1;
    result->vals[5] = 1;
    result->vals[10] = 1;
    result->vals[15] = 1;
}

void rotateMatrix(mat4 *result, mat4 *in, vec3 *axis, float angle) {
    vec3 normalized;
    normal(&normalized, axis); //axis vector has to be unit vector

    mat4 rotationModifier; //stores the rotationModifier matrix used
	rotationModifier.vals[0] = cos(angle) + normalized.x * normalized.x * (1 - cos(angle));
	rotationModifier.vals[1] = normalized.x * normalized.y * (1 - cos(angle)) + normalized.z * sin(angle);
	rotationModifier.vals[2] = normalized.z * normalized.x * (1 - cos(angle)) - normalized.y * sin(angle);
	rotationModifier.vals[3] = 0;

	rotationModifier.vals[4] = normalized.x * normalized.y * (1 - cos(angle)) - normalized.z * sin(angle);
	rotationModifier.vals[5] = cos(angle) + normalized.y * normalized.y * (1 - cos(angle));
	rotationModifier.vals[6] = normalized.z * normalized.y * (1 - cos(angle)) + normalized.x * sin(angle);
	rotationModifier.vals[7] = 0;

	rotationModifier.vals[8] = normalized.x * normalized.z * (1 - cos(angle)) + normalized.y * sin(angle);
	rotationModifier.vals[9] = normalized.y * normalized.z * (1 - cos(angle)) - normalized.x * sin(angle);
	rotationModifier.vals[10] = cos(angle) + normalized.z * normalized.z * (1 - cos(angle));
	rotationModifier.vals[11] = 0;

	rotationModifier.vals[12] = 0;
	rotationModifier.vals[13] = 0;
	rotationModifier.vals[14] = 0;
	rotationModifier.vals[15] = 1;

    multiplyMatrices(result, &rotationModifier, in);
}

void scaleMatrix(mat4 *result, mat4 *in, vec3 *scale) {
    mat4 scaleModifier; //stores the scale matrix used;
    
    for(int i = 0; i < 16; i++) {
        scaleModifier.vals[i] = 0;
    }

    scaleModifier.vals[0] = scale->x;
    scaleModifier.vals[5] = scale->y;
    scaleModifier.vals[10] = scale->z;
    scaleModifier.vals[15] = 1;

    multiplyMatrices(result, &scaleModifier, in);
}

void translateMatrix(mat4 *result, mat4 *in, vec3 *translation) {
    mat4 translationModifier; //stores the translation matrix used

    for(int i = 0; i < 16; i++) {
        translationModifier.vals[i] = 0;
    }

    translationModifier.vals[0] = 1;    //set up diagonals
    translationModifier.vals[5] = 1;
    translationModifier.vals[10] = 1;
    translationModifier.vals[15] = 1;

    translationModifier.vals[12] = translation->x;  //set up actual translation values
    translationModifier.vals[13] = translation->y;
    translationModifier.vals[14] = translation->z;

    multiplyMatrices(result, &translationModifier, in);
}

void orthoMatrix(mat4 *result, float left, float right, float bottom, float top, float near, float far) {
    for(int i = 0; i < 16; i++) {
        result->vals[i] = 0;
    }

    result->vals[0] = 2 / (right - left);

    result->vals[5] = 2 / (top - bottom);

    result->vals[10] = 2 / (near - far);

    result->vals[12] = (right + left) / (left - right);
    result->vals[13] = (top + bottom) / (bottom - top);
    result->vals[14] = (far + near) / (near - far);
    result->vals[15] = 1;
}

void perspectiveMatrix(mat4 *result, float fov, float aspect, float near, float far) {
    float top = near * tan(M_PI / 180 * fov / 2);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;

    for(int i = 0; i < 16; i++) {
        result->vals[i] = 0;
    }

    result->vals[0] = 2 * near / (right - left);

    result->vals[5] = 2 * near / (top - bottom);

    result->vals[8] = (right + left) / (right - left);
    result->vals[9] = (top + bottom) / (top - bottom);
    result->vals[10] = (far + near) / (near - far);
    result->vals[11] = -1;

    result->vals[14] = 2 * far * near / (near - far);
}

void lookAt(vec3 *cameraPos, vec3 *targetPos, vec3 *upVector) {
     
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

void setUniformMatrix(GLuint program, char *name, mat4 *in) {
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, in->vals);
}

void destroyMatrix(mat4 *mat) {
    //nothing to do when destroying matrix
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
