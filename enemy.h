#ifndef GAME_ENEMY
#define GAME_ENEMY

#include "random.h"
#include "actor.h"

enum Movement {SIN, CIRCLE, STRAIGHT};

class Enemy : public Actor {
public:
	int damage = 1;
	float radius = 2;
	int health = 1;

	int score_kill = 100;

	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);

	int countdown_max = 60;
	int  countdown = 0;

	float speed = 1.5;
	float time = 0.0;
	enum Movement mov = Movement::SIN;

	float livetime = 0;
	

	Enemy() {
		Random random = Random();
		float r = random.randfloat();



	}


	void update() {
		Actor::update();
		time += 0.08f;

		livetime += 1;

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