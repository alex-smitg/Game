#ifndef GAME_ENEMY
#define GAME_ENEMY


#include "actor.h"

class Enemy : public Actor {
public:
	float damage = 100;
	float radius = 20;
	float health = 10;


	void update() {
		Actor::update();

		for (Actor* actor : childrens) {
			actor->transform = transform;
		}
	}

	void draw() {
		Actor::draw();
	}


};



#endif