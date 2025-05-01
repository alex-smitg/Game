#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transform.h"

class PointLight {
public:
	glm::vec3 color;
	GLfloat strength;
	unsigned int VBO, VAO;

	Transform transform;
	float radius = 3.0;

	PointLight(glm::vec3 color = glm::vec3(1.0, 1.0, 1.0), GLfloat strength = 1.0) {
		this->strength = strength;
		this->color = color;
	}
};