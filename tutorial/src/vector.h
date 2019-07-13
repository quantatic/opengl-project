#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

void initializeVector(vec3 *result, float x, float y, float z);

void destroyVector(vec3 *in);

//result can be the same as input
void crossProduct(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void normal(vec3 *result, vec3 *in);

//result can be the same as input
void add(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void subtract(vec3 *result, vec3 *a, vec3 *b);

//result can be the same as input
void multiply(vec3 *result, vec3 *a, float scalar);

//result can be the same as input
void divide(vec3 *result, vec3 *a, float scalar);

#endif
