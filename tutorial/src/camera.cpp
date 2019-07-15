#include "camera.hpp"
#include "matrix.hpp"
#include "vector.hpp"

#include <cmath>
#include <iostream>

camera::camera() :
	pos(vec3(0, 0, 0)),
	up(vec3(0, 1, 0)),
	pitch(0),
	yaw(0),
	roll(0)
{ };

mat4 camera::getViewMatrix() const {
	vec3 lookDirection = vec3(
			cos(pitch) * cos(yaw), 
		    sin(pitch), 
 			cos(pitch) * sin(yaw)
		).normal();

	return mat4::lookAt(pos, pos + lookDirection, up);
}

void camera::processMouseMovement(float xOffset, float yOffset) {
	yaw += xOffset;
	pitch += yOffset;

	if(pitch + 0.01 > M_PI / 2) {
		pitch = M_PI / 2;
		pitch -= 0.01;
	}

	if(pitch - 0.01 < -M_PI / 2) {
		pitch = -M_PI / 2;
		pitch += 0.01;
	}
}

void camera::processKeyPress(MOVEMENT_DIRECTION dir) {
	vec3 lookDirection = vec3(
			cos(pitch) * cos(yaw), 
		    sin(pitch), 
 			cos(pitch) * sin(yaw)
		).normal();

	vec3 rightDirection = lookDirection.cross(up).normal();

	float moveSpeed = 0.001;

	if(dir == FORWARD) {
		pos += lookDirection * moveSpeed;
	}

	if(dir == BACKWARD) {
		pos -= lookDirection * moveSpeed;
	}

	if(dir == RIGHT) {
		pos += rightDirection * moveSpeed;
	}

	if(dir == LEFT) {
		pos -= rightDirection * moveSpeed;
	}

}

camera::~camera() { }
