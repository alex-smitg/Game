#ifndef GAME_CAMERA
#define GAME_CAMERA


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera {
public:
	glm::mat4 view;
	glm::vec3 position;

	Camera() {
		view = glm::mat4(1.0);
		position = glm::vec3(0.0);
	}
};

#endif
