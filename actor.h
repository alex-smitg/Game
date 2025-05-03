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

	std::vector<Actor*> childrens;

	

	void setName(std::string name) {
		this->name = name;
	}

	std::vector<Actor*> getChildren() {
		return childrens;
	}

	Actor* findChild(std::string name) {
		for (Actor* actor : childrens) {
			if (actor->name == name) {
				return actor;
			}
		}
	}


	void addChild(Actor* actor) {
		childrens.push_back(actor);
	}

	virtual void draw() {
		for (Actor* actor : childrens) {
			actor->draw();
		}
	}

	virtual void update() {
		for (Actor* actor : childrens) {
			actor->update();
		}
	}
};


#endif