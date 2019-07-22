#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "matrix.hpp"
#include "vector.hpp"

#include <GLFW/glfw3.h>

class Camera {
	Vec3 pos;
	Vec3 up;
	float pitch;
	float yaw;

	float moveSpeed;
	float mouseSensitivity;

	float lastMouseX;
	float lastMouseY;

	public:
		enum CameraMovement {
			LOCAL_FORWARD,
			LOCAL_BACKWARD,
			LOCAL_RIGHT,
			LOCAL_LEFT,
			PITCH,
			YAW,
		};

		Camera();

		Vec3 getLookDirection() const;
		Mat4 getViewMatrix() const;
		
		void move(CameraMovement type, float amount);

		~Camera();
};

#endif
