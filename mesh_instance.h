#ifndef MESH_INSTANCE
#define MESH_INSTANCE


#include "mesh.h"
#include "game_actor.h"

class MeshInstance : public GameActor {
public:
	Mesh* mesh = nullptr;

	void draw() {
		if (mesh != nullptr) {
			mesh->draw();
		}
	}

	void update() {
		if (mesh != nullptr) {
			mesh->transform = transform;
		}
	}


};


#endif