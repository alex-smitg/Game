#ifndef GAME_ENEMY
#define GAME_ENEMY


#include "actor.h"

enum Movement {SIN};

class Enemy : public Actor {
public:
	int damage = 1;
	float radius = 2;
	int health = 1;

	int score_kill = 100;

	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);

	int countdown_max = 60;
	int  countdown = 120;

	float speed = 0.1;
	float time = 0.0;
	enum Movement mov = Movement::SIN;

	void update() {
		Actor::update();
		time += 0.01f;

		countdown -= 1;

		switch (mov) {
		case Movement::SIN:
			transform.position += direction * speed;
			transform.position.x += sin(time) / 10.0;

			break;
		}
	}

	void draw() {
		Actor::draw();
	}


};



#endif