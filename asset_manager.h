#ifndef GAME_ASSET_MANAGER
#define GAME_ASSET_MANAGER

#include <map>

#include "mesh.h"
#include "models.h"
#include "shader.h"
#include "shaders.h"

class AssetManager {
public:
	

	AssetManager() {
		for (auto const& [name, vertices] : models) {
			Mesh* mesh = new Mesh(vertices);
		}



		Shader* standart = new Shader(shaders["standart.vertex"], shaders["standart.fragment"]);
		Shader* font = new Shader(shaders["font.vertex"], shaders["standart.fragment"]);
		_shaders["standart"] = standart;
		_shaders["font"] = font;
	}

	Mesh* getMesh(std::string name) {
		return meshes[name];
	}

	Shader* getShader(std::string name) {
		return _shaders[name];
	}
private:
	std::map<std::string, Mesh*> meshes;
	std::map<std::string, Shader*> _shaders;

};



#endif
