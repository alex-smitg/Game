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
#include "random.h"
#include "camera_controller.h"
#include "font.h"
#include "player.h"

void key_callback(GLFWwindow* _window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* _window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* _window, int width, int height);

Window window(600, 600, "Game");
Camera camera;

int main() {

	
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    glfwSetKeyCallback(window.getWindow(), key_callback);
    glfwSetMouseButtonCallback(window.getWindow(), mouse_button_callback);

	AssetManager assetManager;

    Random random;
	
    //Font font = Font(assetManager.getShader("font"), fontTexture);

    assetManager.createMaterial("test");

    MeshInstance* meshInstance = new MeshInstance("Arrow");
    meshInstance->setMesh(assetManager.getMesh("ship01.obj"));
    meshInstance->setShader(assetManager.getShader("standart"));
    meshInstance->setMaterial(assetManager.getMaterial("test"));
    meshInstance->transform.position.z = 5;

    assetManager.getMaterial("test")->diffuse_texture = assetManager.getTexture("test.png");

    

    Player player;

    
    Font font(assetManager.getShader("font"), assetManager.getTexture("font.png"));

    Scene scene;
    scene.addChild(meshInstance);

   
    CameraController cameraController;
    cameraController.camera = &camera;



    const double targetFPS = 60.0;
    const double frameDuration = 1.0 / targetFPS; // 0.01666...

    double lastTime = glfwGetTime();

    while (!window.shouldClose()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //bg color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        int fov = 70;
        float aspectRatio = 1.0;


        if (delta >= frameDuration) {
            window.pollEvents();

            scene.update();

            camera.projection = glm::perspective(camera.fov / 180.0f * 3.14f, camera.aspectRatio, 0.1f, 5500.0f);
            cameraController.processKeyboard(window.getWindow(), delta);
            cameraController.processMouse(&window);

            camera.transform = player.transform;


            Shader* standart = assetManager.getShader("standart");
            standart->use();
            standart->setMat4("view", camera.view);
            standart->setMat4("projection", camera.projection);

            Actor* actor = scene.getChild("Arrow");
            actor->transform.position.z = sin(glfwGetTime()) * 10.0;

            scene.draw();


            glDisable(GL_CULL_FACE);
            glClear(GL_DEPTH_BUFFER_BIT);



            float logicalWidth = 100.0f; //????
            float logicalHeight = logicalWidth / camera.aspectRatio;

            glm::mat4 proj = glm::ortho(
                0.0f, logicalWidth,
                0.0f, logicalHeight,
                -1.0f, 1.0f
            );


            assetManager.getShader("font")->use();

            font.draw("hello hpw are you doing, im fine\n yes", glm::vec2(0.0, 0.0), &proj);


            font.color = glm::vec3(1.0, 0.0, 0.0);
            font.draw(std::to_string(glfwGetTime()), glm::vec2(glfwGetTime(), glfwGetTime()), &proj);
            font.color = glm::vec3(1.0, 0.0, 1.0);

            glEnable(GL_CULL_FACE);

            glBindVertexArray(0);

            window.swapBuffers();
        }
    }


	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void framebuffer_size_callback(GLFWwindow* _window, int width, int height)
{
	glViewport(0, 0, width, height);

	//glViewport(0, 0, width, height);
	window.width = width;
	window.height = height;
	camera.aspectRatio = (float)width / (float)height;
	if ((int)height == 0) {
        camera.aspectRatio = 1;
	}
	//glBindTexture(GL_TEXTURE_2D, pickingTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == 1) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == 0) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}


#endif