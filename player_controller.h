#ifndef GAME_PLAYER_CONTROLLER
#define GAME_PLAYER_CONTROLLER


#include "player.h"

class PlayerController {
public:
	Player* player;
	float speed = 0.2f;
	float sensitivity = 0.004f;




	float countdown_max = 10;
	float countdown = countdown_max;



	glm::vec3 velocity = glm::vec3(0.0, 0.0, 0.0);

	void processKeyboard(GLFWwindow* window, float deltaTime) {
		
		//glm::vec3 direction(
		//	cos(camera->verticalAngle) * sin(camera->horizontalAngle),
		//	sin(camera->verticalAngle),
		//	cos(camera->verticalAngle) * cos(camera->horizontalAngle)
		//);
		//
		//glm::vec3 right = glm::vec3(
		//	sin(camera->horizontalAngle - 3.14f / 2.0f),
		//	0,
		//	cos(camera->horizontalAngle - 3.14f / 2.0f)
		//);
		//
		//glm::vec3 up = glm::cross(right, direction);
	
		//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//	camera->transform.position += (direction * speed );
		//			
		//}
		//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		//	camera->transform.position += -direction * speed;
		//}
		//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		//	camera->transform.position += right * speed;
		//}
		//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//	camera->transform.position += -right * speed;
		//}

		//camera->view = glm::lookAt(
		//	camera->transform.position,           // Camera is here
		//	camera->transform.position + direction, // and looks here : at the same position, plus "direction"
		//	up                  // Head is up (set to 0,-1,0 to look upside-down)
		//);
	}

	void processInput(Window* window) {

		velocity = glm::vec3(0.0);

		if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
			velocity.y = 1;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
			velocity.y = -1;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
			velocity.x = 1;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
			velocity.x = -1;
		}



		velocity = velocity * speed;
		

		player->transform.position += velocity;
		
		countdown -= 1;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_X) == GLFW_PRESS && countdown <= 0) {
			player->shoot();
			countdown = countdown_max;
		}



		/*double xpos, ypos;
		glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
		glfwSetCursorPos(window->getWindow(), window->width / 2, window->height / 2);
		float xoffset = sensitivity * float(window->width / 2 - xpos);
		float yoffset = sensitivity * float(window->height / 2 - ypos);*/
	}
};

#endif