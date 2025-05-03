#ifndef GAME_PLATER
#define GAME_PLATER


#include "actor.h"

#include "mesh_instance_spawner.h"
#include "mesh_instance.h"

#include "bullet.h"

class Player : public Actor {
public:

    MeshInstanceSpawner *meshInstanceSpawner;

    void shoot() {
        Actor* parent = findChild("bullets");
        MeshInstance* mi = meshInstanceSpawner->spawn(parent);
        Bullet* bullet = new Bullet();
        bullet->addChild(mi);
        parent->addChild(bullet);
        bullet->transform = transform;
    }

    void draw() {
        Actor::draw();
    }

    void update() {
        Actor::update();

    }
};


#endif