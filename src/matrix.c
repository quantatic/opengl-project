#include <math.h>

#include "matrix.h"

//column major rotation matrix
mat4 rotationMatrix(float x, float y, float z, float angle) {
    float scale = sqrt(x * x + y * y + z * z); //up vector has to be unit vector
    float unitX = x / scale;
    float unitY = y / scale;
    float unitZ = z / scale;

	mat4 result;
	result.vals[0] = cos(angle) + unitX * unitX * (1 - cos(angle));
	result.vals[1] = unitX * unitY * (1 - cos(angle)) + unitZ * sin(angle);
	result.vals[2] = unitZ * unitX * (1 - cos(angle)) - unitY * sin(angle);
	result.vals[3] = 0;

	result.vals[4] = unitX * unitY * (1 - cos(angle)) - unitZ * sin(angle);
	result.vals[5] = cos(angle) + unitY * unitY * (1 - cos(angle));
	result.vals[6] = unitZ * unitY * (1 - cos(angle)) + unitX * sin(angle);
	result.vals[7] = 0;

	result.vals[8] = unitX * unitZ * (1 - cos(angle)) + unitY * sin(angle);
	result.vals[9] = unitY * unitZ * (1 - cos(angle)) - unitX * sin(angle);
	result.vals[10] = cos(angle) + unitZ * unitZ * (1 - cos(angle));
	result.vals[11] = 0;

	result.vals[12] = 0;
	result.vals[13] = 0;
	result.vals[14] = 0;
	result.vals[15] = 1;

    return result;
}

float *matrixPointer(mat4 *in) {
	return in->vals;
}
