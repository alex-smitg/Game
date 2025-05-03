#ifndef GAME_CAMERA
#define GAME_CAMERA


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "actor.h"

class Camera : public Actor {
public:
	glm::mat4 view;
	glm::mat4 projection;

	float fov = 70.0f; // если перспектива
	float aspectRatio = 1.0f;
	float nearPlane = 0.01f;
	float farPlane = 5000.0f;

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;

	Camera() {
		view = glm::mat4(1.0);
		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 5500.0f);
	}
};

#endif
