#ifndef GAME_PLATER
#define GAME_PLATER


#include "actor.h"


class Player : public Actor {
public:
    float yaw = 0.0f;
    float pitch = 0.0f;
    float roll = 0.0f;

    float targetYaw = 0.0f;
    float targetPitch = 0.0f;
    float targetRoll = 0.0f;


    void update_rotation(float deltaYaw, float deltaPitch, float deltaRoll) {
        targetYaw += deltaYaw;
        targetPitch += deltaPitch;
        targetRoll += deltaRoll;

        


        yaw = glm::mix(yaw, targetYaw, 0.25);
        pitch = glm::mix(pitch, targetPitch, 0.25);
        roll = glm::mix(roll, targetRoll, 0.25);

        if (pitch > 3.14 / 2.0 - 0.03) {
            pitch = 3.14 / 2.0 - 0.1;
            targetPitch -= 0.5;
        }

        if (pitch < -3.14 / 2.0 + 0.03) {
            pitch = -3.14 / 2.0 + 0.1;
            targetPitch += 0.5;
        }

 
    }

    void update() {
        Actor::update();


    }
};


#endif