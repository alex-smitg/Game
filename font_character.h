#ifndef GAME_FONT_CHARACTER
#define GAME_FONT_CHARACTER

#include "shader.h"
#include "vector"


class FontCharacter {
public:


	

	float quadVertices[24] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};


	unsigned int quadVAO, quadVBO;

	Texture* texture;
	Shader* shader;
	glm::vec2 char_pos = glm::vec2(1.0f, 0.0f);

	glm::vec2 position = glm::vec2(0.0, 0.0);

	glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);

	void draw() {

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		shader->Use();
		shader->setVec3("color", color);
		shader->setVec2("char_pos", char_pos);
		shader->setVec2("position", position);
		shader->setFloat("scale", 0.03);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->id);
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	
	FontCharacter(Shader* shader) {
		this->shader = shader;
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	}
};


#endif