#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

vec3 crossProduct(vec3 a, vec3 b);

vec3 normal(vec3 in);

#endif
