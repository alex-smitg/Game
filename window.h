#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <string>

class Window {

	Window(int width, int height, std::string title) {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (window == nullptr) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
	}

		




};



#endif