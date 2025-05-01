#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Texture {
public:
	GLuint id;
	std::string path;


	//~Texture() {
		//glDeleteTextures(1, &id);
	//}
};