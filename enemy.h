#ifndef GAME_ENEMY
#define GAME_ENEMY


#include "actor.h"

enum Movement {SIN};

class Enemy : public Actor {
public:
	int damage = 1;
	float radius = 1;
	int health = 1;


	enum Movement

	void update() {
		Actor::update();

		
	}

	void draw() {
		Actor::draw();
	}


};



#endif