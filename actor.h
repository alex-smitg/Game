#ifndef GAME_ACTOR
#define GAME_ACTOR

#include <vector>
#include <string>

#include "transform.h"

class Actor {
public:
	Transform transform;
	bool visible = true;
	std::string name = "";

	bool is_killed = false;
	

	void setName(std::string name) {
		this->name = name;
	}







	virtual void draw() {}

	virtual void update() {}
};


#endif