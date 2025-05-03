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
#include "scene.h"
#include "mesh_instance.h"
#include "camera.h"

int main() {

	Window window(600, 600, "Game");

	AssetManager assetManager;
	

    assetManager.createMaterial("test");

    MeshInstance* meshInstance = new MeshInstance("Arrow");
    meshInstance->setMesh(assetManager.getMesh("arrow.obj"));
    meshInstance->setShader(assetManager.getShader("standart"));
    meshInstance->setMaterial(assetManager.getMaterial("test"));
    meshInstance->transform.position.z = 5;

    Scene scene;
    scene.addChildren(meshInstance);

    Camera camera;





    const double targetFPS = 60.0;
    const double frameDuration = 1.0 / targetFPS; // 0.01666...

    double lastTime = glfwGetTime();

    while (!window.shouldClose()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //bg color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        int fov = 79;
        float aspectRatio = 1.0;


        if (delta >= frameDuration) {
            window.pollEvents();

            scene.update();


            Shader* standart = assetManager.getShader("standart");
            standart->use();
            standart->setMat4("view", camera.view);
            standart->setMat4("projection", camera.projection);

            Actor* actor = scene.getChildren("Arrow");
            actor->transform.position.z = sin(glfwGetTime()) * 10.0;

            scene.draw();

            window.swapBuffers();
        }
    }


	return 0;
}


#endif