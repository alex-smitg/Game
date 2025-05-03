#ifndef GAME_BULLET
#define GAME_BULLET


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "actor.h"
#include "transform.h"

class Bullet : public Actor {
public:
	bool is_enemy = false;

	float speed = 2.0;

	void update() {
		Actor::update();

		for (Actor* actor : childrens) {
			actor->transform = transform;
		}

		transform.position.y += speed;
	}

	void draw() {
		Actor::draw();
	}
};


#endif



