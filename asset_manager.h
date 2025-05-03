#ifndef GAME_ASSET_MANAGER
#define GAME_ASSET_MANAGER

#include <map>

#include "mesh.h"
#include "models.h"


class AssetManager {
public:
	std::map<std::string, Mesh*> meshes;

	AssetManager() {
		for (auto const& [name, vertices] : models) {
			Mesh* mesh = new Mesh(vertices);
		}
	}

	Mesh* getMesh(std::string name) {
		return meshes[name];
	}
};


#endif
