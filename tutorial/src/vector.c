#include "vector.h"

#include <math.h>

void initializeVector(vec3 *result, float x, float y, float z) {
	result->x = x;
	result->y = y;
	result->z = z;
}

void destroyVector(vec3 *in) {
    //nothing to do for destroying vector
}

void crossProduct(vec3 *result, vec3 *a, vec3 *b) {
    float resX = a->y * b->z - a->z - b->y;
    float resY = a->z * b->x - a->x * b->z;
    float resZ = a->x * b->y - a->y * b->x;

    result->x = resX;
    result->y = resY;
    result->z = resZ;
}

void normal(vec3 *result, vec3 *in) {
    float magnitude = sqrt(in->x * in->x + in->y * in->y + in->z * in->z);

    result->x = in->x / magnitude;
    result->y = in->y / magnitude;
    result->z = in->z / magnitude;
}

void add(vec3 *result, vec3 *a, vec3 *b) {
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
}

void subtract(vec3 *result, vec3 *a, vec3 *b) {
    result->x = a->x - b->x;
    result->y = a->y - b->y;
    result->z = a->z - b->z;
}

void multiply(vec3 *result, vec3 *a, float scalar) {
    result->x = a->x * scalar;
    result->y = a->y * scalar;
    result->z = a->z * scalar;
}

void divide(vec3 *result, vec3 *a, float scalar) {
    result->x = a->x / scalar;
    result->y = a->y / scalar;
    result->z = a->z / scalar;
}
