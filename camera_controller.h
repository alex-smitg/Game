#ifndef GAME_CAMERA_CONTROLLER
#define GAME_CAMERA_CONTROLLER


#include "camera.h"

class CameraController {
public:
	Camera* camera;
	float speed = 1.0f;
	float sensitivity = 0.005f;

	bool left_mouse_clicked = false;

	void processKeyboard(GLFWwindow* window, float deltaTime) {
		if (camera->verticalAngle < -3.14f / 2.0f) camera->verticalAngle = -3.14f / 2.0f;
		if (camera->verticalAngle > 3.14f / 2.0f) camera->verticalAngle = 3.14f / 2.0f;
		
		glm::vec3 direction(
			cos(camera->verticalAngle) * sin(camera->horizontalAngle),
			sin(camera->verticalAngle),
			cos(camera->verticalAngle) * cos(camera->horizontalAngle)
		);
		
		glm::vec3 right = glm::vec3(
			sin(camera->horizontalAngle - 3.14f / 2.0f),
			0,
			cos(camera->horizontalAngle - 3.14f / 2.0f)
		);
		
		glm::vec3 up = glm::cross(right, direction);
	
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera->transform.position += (direction * speed );
					
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera->transform.position += -direction * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera->transform.position += right * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera->transform.position += -right * speed;
		}

		camera->view = glm::lookAt(
			camera->transform.position,           // Camera is here
			camera->transform.position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
	}

	void processMouse(Window* window) {
		if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			
			if (left_mouse_clicked == false) {
				left_mouse_clicked = true;
				glfwSetCursorPos(window->getWindow(), window->width/ 2, window->height / 2);
			}
			
			double xpos, ypos;
			glfwGetCursorPos(window->getWindow(), &xpos, &ypos);
			glfwSetCursorPos(window->getWindow(), window->width / 2, window->height / 2);
			camera->horizontalAngle += sensitivity * float(window->width / 2 - xpos);
			camera->verticalAngle += sensitivity * float(window->height / 2 - ypos);
		}
		if (glfwGetMouseButton(window->getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
			left_mouse_clicked = false;
		}
	}
};

#endif