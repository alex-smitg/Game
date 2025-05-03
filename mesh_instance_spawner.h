#ifndef MESH_INSTANCE_SPAWNER
#define MESH_INSTANCE_SPAWNER




#include "mesh.h"
#include "shader.h"
#include "material.h"

#include "mesh_instance.h"

class MeshInstanceSpawner {
public:
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	Material* material = nullptr;


	int count = 0; //

	std::string name = ""; 

	MeshInstanceSpawner(Mesh* mesh, Shader* shader, Material* material, std::string name) {
		this->mesh = mesh;
		this->shader = shader;
		this->material = material;
		this->name = name;
	}


	MeshInstance* spawn(Actor* parent) {
		MeshInstance* meshInstance = new MeshInstance(name + std::to_string(count));
		meshInstance->setMesh(mesh);
		meshInstance->setShader(shader);
		meshInstance->setMaterial(material);
		count += 1;
		return meshInstance;
	}
};

#endif