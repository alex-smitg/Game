#ifndef GAME_ACTOR
#define GAME_ACTOR

#include "transform.h"

class Actor {
public:
	Transform transform;
	bool visible = true;


	virtual void draw() {

	}

	virtual void update() {

	}
};


#endif