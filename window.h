#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <string>

class Window {
public:
	Window(int width, int height, std::string title) {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (window == nullptr) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);
			
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

	}

	void pollEvents() const {
		glfwPollEvents();
	}

	void swapBuffers() const {
		glfwSwapBuffers(window);
	}

	bool shouldClose() const{
		return glfwWindowShouldClose(window);
	}
private:
	GLFWwindow* window;
};


#endif