#ifndef MESH_INSTANCE
#define MESH_INSTANCE


#include "mesh.h"
#include "actor.h"

class MeshInstance : public Actor {
public:
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	Material* material = nullptr;


	MeshInstance(std::string name) {
		this->name = name;
	}

	void setMesh(Mesh* mesh) {
		this->mesh = mesh;
	}

	void setShader(Shader* shader) {
		this->shader = shader;
	}

	void setMaterial(Material* material) {
		this->material = material;
	}
	
	void draw() {
		shader->use();
		shader->setMat4("model", transform.get_matrix());

		if (material != nullptr && shader != nullptr) {
			shader->setFloat("spec_factor", material->specular_value);
			shader->setFloat("shine", material->shine_value);
			shader->setVec3("diffuse_color", material->diffuse_color);
			shader->setVec2("uv_scale", material->uv_scale);
			shader->setInt("emit", material->emit);

			if (material->diffuse_texture != nullptr) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, material->diffuse_texture->id);
			}
		}
		if (mesh != nullptr) {
			mesh->draw();
		}

		

	}

	void update() {

	}


};


#endif