#ifndef GAME_WINDOW
#define GAME_WINDOW

#include <string>

class Window {
public:
	int width = 600;
	int height = 600;

	unsigned int pickingTexture;

	Window(int width, int height, std::string title) {
		glfwInit();

		this->width = width;
		this->height = height;

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




		unsigned int pickingFBO;
			glGenFramebuffers(1, &pickingFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);
		
			
			glGenTextures(1, &pickingTexture);
			glBindTexture(GL_TEXTURE_2D, pickingTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);



	}



	GLFWwindow* getWindow() {
		return window;
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