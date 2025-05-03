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
#include "player_controller.h"
#include "font.h"
#include "player.h"
#include "mesh_instance_spawner.h"
#include "enemy.h"

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
    Scene scene;


    for (int i = 0; i < 30; i++) {
        MeshInstance* meshInstance = new MeshInstance("Arrow" + std::to_string(i));
        meshInstance->setMesh(assetManager.getMesh("ship01.obj"));
        meshInstance->setShader(assetManager.getShader("standart"));
        meshInstance->setMaterial(assetManager.getMaterial("test"));
        meshInstance->transform.position.z = random.randfloat() * 80.0f - 40.0f;
        meshInstance->transform.position.y = random.randfloat() * 80.0f - 40.0f;
        meshInstance->transform.position.x = random.randfloat() * 80.0f - 40.0f;
        scene.addChild(meshInstance);
    }


    assetManager.getMaterial("test")->diffuse_texture = assetManager.getTexture("test.png");

    

    Player player;
    player.setName("player");
    scene.addChild(&player);



    MeshInstanceSpawner bulletSpawner(assetManager.getMesh("bullet.obj"), assetManager.getShader("standart"), assetManager.getMaterial("test"), "bullet");

    MeshInstanceSpawner enemySpawner(assetManager.getMesh("ship01.obj"), assetManager.getShader("standart"), assetManager.getMaterial("test"), "enemy");


    Actor* enemy_parent = new Actor();
    enemy_parent->name = "enemies";
    scene.addChild(enemy_parent);
    

   


    MeshInstance* meshInstance = new MeshInstance("Arrow_player");
    meshInstance->setMesh(assetManager.getMesh("ship01.obj"));
    meshInstance->setShader(assetManager.getShader("standart"));
    meshInstance->setMaterial(assetManager.getMaterial("test"));
    scene.addChild(meshInstance);


    MeshInstance* terrain = new MeshInstance("terrain");
    terrain->setMesh(assetManager.getMesh("terrain.obj"));
    terrain->setShader(assetManager.getShader("standart"));
    terrain->setMaterial(assetManager.getMaterial("test"));
    //scene.addChild(terrain);
    
    Font font(assetManager.getShader("font"), assetManager.getTexture("font.png"));


    Actor* bullets = new Actor();
    bullets->setName("bullets");
    player.addChild(bullets);
    player.meshInstanceSpawner = &bulletSpawner;
    
    scene.addChild(&camera);

    PlayerController playerController;
    playerController.player = &player;


    
   

    int spawn_enemy_every = 60;
    int enemy_spawn_countdown = spawn_enemy_every;

    

    const double targetFPS = 60.0;
    const double frameDuration = 1.0 / targetFPS; // 0.01666...


    float camera_y_st = 0;


    double lastTime = glfwGetTime();

    while (!window.shouldClose()) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClearColor(0.0f, 0.0f, 0.1f, 1.0f); //bg color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;

        int fov = 70;
        float aspectRatio = 1.0;


        if (delta >= frameDuration) {
            window.pollEvents();


            playerController.processInput(&window);
           

            camera.projection = glm::perspective(camera.fov / 180.0f * 3.14f, camera.aspectRatio, 0.1f, 5500.0f);
            

            camera_y_st += 0.1;
            player.transform.position.y += 0.1;

            if (player.transform.position.y < camera_y_st) {
                player.transform.position.y = camera_y_st;
            }

            enemy_spawn_countdown -= 1;

            if (enemy_spawn_countdown <= 0) {
                enemy_spawn_countdown = spawn_enemy_every;

                Enemy* enemy = new Enemy();
                enemy->transform = player.transform;
                enemy->transform.position.z = player.transform.position.z;
                enemy->transform.position.y = camera_y_st + 20.0;

                MeshInstance* mi = enemySpawner.spawn(enemy);
                enemy_parent->addChild(enemy);

                
            }

            camera.transform.position = player.transform.position;

            camera.transform.position.x = 0.0f;
            camera.transform.position.z += 25;
            camera.transform.position.y = camera_y_st;
            camera.transform.rotation.x = 0.4;

           /* scene.getChild("terrain")->transform = camera.transform;
            scene.getChild("terrain")->transform.position.y += 6;
            scene.getChild("terrain")->transform.position.z -=  40;*/

            scene.getChild("Arrow1")->transform = player.transform;

            Actor* actor = scene.getChild("Arrow_player");
            actor->transform = player.transform;


            scene.update();

            Shader* standart = assetManager.getShader("standart");
            standart->use();
            standart->setMat4("view", camera.view);
            standart->setMat4("projection", camera.projection);


            for (Actor* actor : scene.getChild("player")->findChild("bullets")->getChildren()) {
                Bullet* bullet = static_cast<Bullet*>(actor);

                for (Actor* _actor : scene.getChild("enemies")->getChildren()) {
                    Enemy* enemy = static_cast<Enemy*>(_actor);

                    float dist_square = glm::dot(glm::vec2(bullet->transform.position.x, bullet->transform.position.y ),
                        glm::vec2(bullet->transform.position.x, bullet->transform.position.y));



                    if (dist_square < enemy->radius * enemy->radius) {
                        bullet->destroy();

                        
                    }
                }
            }

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

            font.draw(
                std::to_string(player.transform.position.x) + "\n" +
                std::to_string(player.transform.position.y) + "\n" +
                std::to_string(player.transform.position.z) + "\n"
                
                , glm::vec2(0.0, logicalHeight - 5.0), &proj);


            font.color = glm::vec3(1.0, 0.0, 0.0);
            font.draw(std::to_string(glfwGetTime())
                , glm::vec2(glfwGetTime(), glfwGetTime()), &proj);
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