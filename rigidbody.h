#ifndef GAME_RIGID_BODY
#define GAME_RIGID_BODY

#include "bullet/btBulletDynamicsCommon.h"


class RigidBody : public GameActor{
public:
	btCollisionShape* collisionShape;
	btRigidBody* rigidBody;

	RigidBody(btDiscreteDynamicsWorld* dynamicsWorld, btCollisionShape* collisionShape, Transform transform, int mass) {
		this->transform = transform;

		this->collisionShape = collisionShape;
		btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
			btQuaternion(0.0, 0.0, 0.0, 1.0),
			btVector3(transform.position.x, transform.position.y, transform.position.z)
		));


		btRigidBody::btRigidBodyConstructionInfo rigidbodyci(
			mass,                  // mass, in kg. 0 -> static object, will never move.
			motionstate,
			collisionShape,  // collision shape of body
			btVector3(0, 0, 0)    // local inertia
		);
		rigidBody = new btRigidBody(rigidbodyci);

		

		dynamicsWorld->addRigidBody(rigidBody);
	}

	void update() {

		btTransform trans;
		rigidBody->getMotionState()->getWorldTransform(trans);

		this->transform.position.x = trans.getOrigin().getX();
		this->transform.position.y = trans.getOrigin().getY();
		this->transform.position.z = trans.getOrigin().getZ();

		this->transform.rotation.x = trans.getRotation().getX();
		this->transform.rotation.y = trans.getRotation().getY();
		this->transform.rotation.z = trans.getRotation().getZ();

	}
};

#endif