#include "camera.hpp"
#include "matrix.hpp"
#include "vector.hpp"

#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <limits>

#define MINIMUM_PITCH (-M_PI / 2 * 0.999)
#define MAXIMUM_PITCH (M_PI / 2 * 0.999)

Camera::Camera() :
	pos(Vec3(0, 0, 0)),
	up(Vec3(0, 1, 0)),
	pitch(0),
	yaw(0)
{ };

Vec3 Camera::getLookDirection() const {
	return Vec3(
			cos(pitch) * sin(-yaw),
			sin(pitch),
			-cos(pitch) * cos(-yaw)
		).normal();
}

Mat4 Camera::getViewMatrix() const {
	return Mat4::lookAt(pos, pos + getLookDirection(), up);
}

void Camera::move(CameraMovement type, float amount) {
	Vec3 lookDirection = getLookDirection();

	Vec3 lookRight = lookDirection.cross(up).normal();

	switch(type) {
		case LOCAL_FORWARD:
			pos += (lookDirection * amount);
			break;
		case LOCAL_BACKWARD:
			pos -= (lookDirection * amount);
			break;
		case LOCAL_RIGHT:
			pos += (lookRight * amount);
			break;
		case LOCAL_LEFT:
			pos -= (lookRight * amount);
			break;
		case PITCH:
			pitch += amount;

			if(pitch >= MAXIMUM_PITCH) {
				pitch = MAXIMUM_PITCH;
			}

			if(pitch <= MINIMUM_PITCH) {
				pitch = MINIMUM_PITCH; 
			}

			break;
		case YAW:
			yaw += amount;
			break;
	}
}

Camera::~Camera() { }
