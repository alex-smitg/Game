#ifndef GAME_PLAYER_CONTROLLER
#define GAME_PLAYER_CONTROLLER


#include "player.h"

class PlayerController {
public:
	Player* player;
	float speed = 0.3f;
	float sensitivity = 0.004f;


	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

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
		


		glm::mat4 yawMat = glm::rotate(glm::mat4(1.0f), player->yaw, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 pitchMat = glm::rotate(glm::mat4(1.0f), player->pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 rollMat = glm::rotate(glm::mat4(1.0f), player->roll, glm::vec3(0.0f, 0.0f, 1.0f));

		front = glm::normalize(glm::vec3(yawMat * pitchMat * rollMat * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f)));
		right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
		up = glm::normalize(glm::cross(right, front));

		glm::vec3 desiredVelocity = glm::vec3(0.0f);
		

		if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
			desiredVelocity += front ;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
			desiredVelocity += -front;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
			desiredVelocity += right;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
			desiredVelocity += -right;
		}

		if (glm::length(desiredVelocity) > 0.0f)
			desiredVelocity = glm::normalize(desiredVelocity) * speed;

		velocity = glm::mix(velocity, desiredVelocity, 0.1f);

		player->transform.position += velocity;
		




		double xpos, ypos;
		glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
		glfwSetCursorPos(window->getWindow(), window->width / 2, window->height / 2);
		float xoffset = sensitivity * float(window->width / 2 - xpos);
		float yoffset = sensitivity * float(window->height / 2 - ypos);

		player->update_rotation(xoffset, yoffset, 0.0);
	}
};

#endif