#ifndef GAME_PLAYER
#define GAME_PLAYER

#include "transform.h"
#include "camera.h"
#include "game_actor.h"
#include "rigidbody.h"
#include "transform.h"

class Player : public GameActor {
public:
	Camera camera;
	RigidBody* rigidbody;


	Player(btDiscreteDynamicsWorld* dynamicsWorld, btCollisionShape* collisionShape, int mass, Transform transform) {
		rigidbody = new RigidBody(dynamicsWorld, collisionShape, transform, mass);
	}
	void update() {
		
		rigidbody->update();
		this->transform = rigidbody->transform;
		camera.position = transform.position;
	}
};

#endif