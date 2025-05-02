#ifndef GAME_CELL
#define GAME_CELL


#include "mesh.h"
#include "game_actor.h"
#include "mesh_instance.h"

class Cell : public GameActor {
public:
	MeshInstance* meshInstance;

	Cell() {
		meshInstance = new MeshInstance();
	}

	void update() {
		meshInstance->update();
		meshInstance->transform = transform;
	}

	void draw() {
		meshInstance->draw();
	}

	void setMesh(Mesh* mesh) {
		meshInstance->mesh = mesh;
	}
};


#endif