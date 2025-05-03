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
	int damage = 1.0;

	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);

	float livetime = 0;

	void update() {
		Actor::update();
		livetime += 1;

		transform.position += direction * speed;
	}

	void draw() {
		Actor::draw();
	}


};


#endif



