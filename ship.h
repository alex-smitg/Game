#ifndef GAME_SHIP
#define GAME_SHIP

#include <string>

#include "game_actor.h"
#include "mesh_instance.h"
#include "shader.h"

class Ship : public GameActor {
public:
	MeshInstance* meshInstance;

	int id;

	float speed = 0.5f;
	bool can_control = true;

	bool is_enemy = false;

	bool moving = false;

	float acc = 0.0;
	float acc_speed = 0.01;

	int health = 5000;
	
	int attack_radius = 50;
	bool attacking = false;
	bool moving_to_enemy = true;
	Ship* target = nullptr;

	glm::vec3 end_pos = glm::vec3(0.0);

	float distance = 0;

	int next_move = 0;

	int rocket_countdown = 0;

	int damage = 20;





	std::string name = "";


	void attack(Ship *target) {
		std::cout << name + " attacking " + target->name + "\n";
		moving_to_enemy = true;
		navigate(target->transform.position);

		this->target = target;
	}


	void navigate(glm::vec3 end_pos) {
		std::cout << name + " navigating" + "\n";

		this->end_pos = end_pos;

		moving = true;
	}


	void draw() {
		meshInstance->transform = transform;
		meshInstance->draw();
	}

	void update() {
		
		meshInstance->update();


		

		if (this->target != nullptr) {
			distance = glm::distance(target->transform.position, transform.position);
			if (distance < attack_radius && moving_to_enemy == true) {
				moving_to_enemy = false;
				moving = false;
				attacking = true;
				
				
			}

			if(attacking) {
				target->health -= damage;

				rocket_countdown += 1;
			}


			if (distance > attack_radius && moving_to_enemy==true) {
				this->target = nullptr;
			}
		}


		if (moving == true) {
			glm::vec3 norm_dir = glm::normalize(end_pos - transform.position);
			transform.position += norm_dir * (speed * acc);
			acc += acc_speed;
			if (acc >= 1.0) {
				acc = 1.0;
			}
			distance = glm::distance(end_pos, transform.position);

			if (distance <= 1.0f) {
				moving = false;
				acc = 0;
			}
		}

	}
};

#endif