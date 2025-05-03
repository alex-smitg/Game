#ifndef GAME_MAIN
#define GAME_MAIN

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8
#include <stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Game.h"

#include "asset_manager.h"
#include "window.h"

int main() {

	Window window(600, 600, "Game");

	AssetManager assetManager;
	assetManager.getMesh("arrow.obj");


    const double targetFPS = 60.0;
    const double frameDuration = 1.0 / targetFPS; // 0.01666...

    double lastTime = glfwGetTime();

    while (!window.shouldClose()) {
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        if (delta >= frameDuration) {
            window.pollEvents();
            window.swapBuffers();
        }
    }


	return 0;
}


#endif