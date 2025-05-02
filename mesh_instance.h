#ifndef MESH_INSTANCE
#define MESH_INSTANCE


#include "mesh.h"
#include "game_actor.h"

class MeshInstance : public GameActor {
public:
	Mesh* mesh = nullptr;

	bool visible = true;

	void draw() {
		if (mesh != nullptr && visible == true) {
			mesh->transform = transform;
			mesh->draw();
		}
	}

	void update() {
		if (mesh != nullptr) {
			
		}
	}


};


#endif