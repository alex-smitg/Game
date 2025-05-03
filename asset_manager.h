#ifndef GAME_ASSET_MANAGER
#define GAME_ASSET_MANAGER

#include <map>

#include "mesh.h"
#include "material.h"
#include "shader.h"

#include "models.h"
#include "shaders.h"


class AssetManager {
public:
	

	AssetManager() {
		for (auto const& [name, vertices] : models) {
			Mesh* mesh = new Mesh(vertices);
			meshes[name] = mesh;
		}



		Shader* standart = new Shader(shaders["standart.vertex"], shaders["standart.fragment"]);
		Shader* font = new Shader(shaders["font.vertex"], shaders["standart.fragment"]);
		_shaders["standart"] = standart;
		_shaders["font"] = font;
	}

	Mesh* getMesh(std::string name) {
		return meshes[name];
	}

	Shader* getShader(std::string name)  {
		return _shaders[name];
	}

	Material* createMaterial(std::string name) {
		Material* material = new Material();
		_materials[name] = material;
		return material;
	}
	Material* getMaterial(std::string name) {
		return _materials[name];
	}


private:
	std::map<std::string, Mesh*> meshes;
	std::map<std::string, Shader*> _shaders;
	std::map<std::string, Material*> _materials;

};



#endif
