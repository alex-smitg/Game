#ifndef GAME_MESH
#define GAME_MESH

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>


const int VALUES_PER_VERTEX = 8; //vertices = {{x, y, z, u, v, nx, ny, nz}, ....}  

class Mesh {
public:
	Mesh(std::vector<GLfloat> vertices) {
		this->vertices = vertices;
		init();
	}

	~Mesh() {
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void draw() {
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / VALUES_PER_VERTEX);
	}


private:
	unsigned int VBO, VAO;
	std::vector<GLfloat> vertices;
	int vertex_stride = VALUES_PER_VERTEX * sizeof(GLfloat); //vertices = {{x, y, z, u, v, nx, ny, nz}, ....} 

	void init() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

		//Position x,y,z
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_stride, 0);
		//Uv u,v
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertex_stride, (void*)(3 * sizeof(GLfloat)));
		//Normal nx, ny, nz
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertex_stride, (void*)(5 * sizeof(GLfloat)));
	}
};

#endif