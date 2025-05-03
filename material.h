#ifndef GAME_MATERIAL
#define GAME_MATERIAL

#pragma once

#include "texture.h"

class Material {
public:
	float specular_value = 1.0f;
	float reflection_value = 0.0f;
	float diffuse_value = 1.0f;
	float refract_value = 0.256f;
	float shine_value = 18.0f;

	glm::vec2 uv_scale = { 1.0f, 1.0f };

	bool emit = false;

	glm::vec3 diffuse_color = glm::vec3(1.0f, 1.0f, 1.0f);

	Texture* diffuse_texture = nullptr;

};


#endif GAME_MATERIAL