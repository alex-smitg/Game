#ifndef GAME_PLATER
#define GAME_PLATER


#include "actor.h"

#include "mesh_instance_spawner.h"
#include "mesh_instance.h"

#include "bullet.h"


class Player : public Actor {
public:


    std::vector<Bullet*> *bullets;

    void shoot() {
        Bullet* bullet = new Bullet();
        bullet->transform = transform;
        bullets->push_back(bullet);
    }

    void draw() {
        Actor::draw();
    }

    void update() {
        Actor::update();

    }
};


#endif