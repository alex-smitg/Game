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

	Actor* parent;

	std::vector<Actor*> childrens;

	bool is_destroyed = false;
	

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

		actor->parent = this;
	}

	virtual void destroy() {
		for (Actor* actor : childrens) {
			actor->destroy();
		}

		parent->childrens.erase(std::remove(parent->childrens.begin(), parent->childrens.end(), this), parent->childrens.end());

		is_destroyed = true;

		delete this;
	}

	virtual void draw() {
		for (Actor* actor : childrens) {
			if (actor->is_destroyed) {
				delete actor;
			}
			else {
				actor->draw();

			}
			
		}
	}

	virtual void update() {
		for (Actor* actor : childrens) {
			actor->update();
		}
	}
};


#endif