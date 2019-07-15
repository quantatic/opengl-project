#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrix.hpp"
#include "vector.hpp"

#include <GLFW/glfw3.h>

enum MOVEMENT_DIRECTION {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class camera {
	vec3 pos;
	vec3 up;
	float pitch;
	float yaw;
	float roll;

	public:
		camera();

		mat4 getViewMatrix() const;

		void processMouseMovement(float xOffset, float yOffset);
		void processKeyPress(MOVEMENT_DIRECTION dir);

		~camera();
};

#endif
