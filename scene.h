#ifndef GAME_SCENE
#define GAME_SCENE


#include <map>
#include <string>
#include <vector>

#include "actor.h"


class Scene {
public:


	void update() {
		for (auto const& [name, actor] : childrens) {
			actor->update();
		}
	}

	void draw() {
		for (auto const& [name, actor] : childrens) {
			actor->draw();
		}
	}


	void addChild(Actor* actor) {
		childrens[actor->name] = actor;
	}

	Actor* getChild(std::string name) {
		if (childrens.count(name) == 0) {
			std::cout << "NO CHILD WITH NAME: " << name << std::endl;
		}
		return childrens[name];
	}




private:
	std::map<std::string, Actor*> childrens;

};

#endif