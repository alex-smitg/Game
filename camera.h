#ifndef GAME_CAMERA
#define GAME_CAMERA


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "actor.h"
#include "transform.h"

class Camera : public Actor {
public:
	glm::mat4 view;
	glm::mat4 projection;

	float fov = 70.0f;
	float aspectRatio = 1.0f;
	float nearPlane = 0.01f;
	float farPlane = 5000.0f;

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;

	Camera() {
		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 5500.0f);

		
	}


	void update() {
		Actor::update();

		view = glm::mat4(1.0);
		view = glm::rotate(view, -transform.rotation.x, glm::vec3(1, 0, 0));
		view = glm::rotate(view, -transform.rotation.y, glm::vec3(0, 1, 0));
		view = glm::rotate(view, -transform.rotation.z, glm::vec3(0, 0, 1));
		view = glm::translate(view, -transform.position);
	}
};

#endif
