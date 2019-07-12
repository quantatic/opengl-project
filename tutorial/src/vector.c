#include "vector.h"

#include <math.h>

vec3 crossProduct(vec3 a, vec3 b) {
    vec3 result;

    result.x = a.y * b.z - a.z - b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}

vec3 normal(vec3 in) {
    float magnitude = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);

    vec3 result;

    result.x = in.x / magnitude;
    result.y = in.y / magnitude;
    result.z = in.z / magnitude;

    return result;
}
