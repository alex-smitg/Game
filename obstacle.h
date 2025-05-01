#ifndef GAME_OBSTACLE
#define GAME_OBSTACLE

#include "game_actor.h"
#include "mesh.h"
#include "rigidbody.h"


#include "bullet/btBulletDynamicsCommon.h"

class Obstacle : public GameActor
{
public:
	Mesh* mesh = nullptr;
	RigidBody* rigidbody = nullptr;
	Obstacle(btDiscreteDynamicsWorld* dynamicsWorld, btCollisionShape* collisionShape, int mass) {
		rigidbody = new RigidBody(dynamicsWorld,collisionShape, transform, mass);
	}
	~Obstacle();


	void update() {
		
	}

	void draw() {
		mesh->draw();
	}
};
#endif