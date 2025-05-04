#ifndef GAME_MAIN
#define GAME_MAIN

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8
#include <stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <AL/al.h>
#include <AL/alc.h>


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
#include "enemy.h"
#include "collectable.h"



void key_callback(GLFWwindow* _window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* _window, int button, int action, int mods);

void framebuffer_size_callback(GLFWwindow* _window, int width, int height);

Window window(600, 600, "Game");
Camera camera;

#define IDR_WAV1 101


int main() {
    ALCdevice* device = alcOpenDevice(NULL);
    if (!device) {
        std::cerr << "openal error" << std::endl;
        return -1;
    }

    ALCcontext* context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);

    HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_WAV1), "WAV");
    HGLOBAL hData = LoadResource(NULL, hRes);
    DWORD dwSize = SizeofResource(NULL, hRes);
    BYTE* pData = (BYTE*)LockResource(hData);

    short channels = *(short*)(pData + 22);
    int sampleRate = *(int*)(pData + 24);
    short bitsPerSample = *(short*)(pData + 34);

    ALenum format;
    if (channels == 1 && bitsPerSample == 8) format = AL_FORMAT_MONO8;
    else if (channels == 1 && bitsPerSample == 16) format = AL_FORMAT_MONO16;
    else if (channels == 2 && bitsPerSample == 8) format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bitsPerSample == 16) format = AL_FORMAT_STEREO16;

    BYTE* audioData = nullptr;
    DWORD audioSize = 0;
    for (DWORD i = 12; i < dwSize - 8; ) {
        char chunkID[5] = { 0 };
        memcpy(chunkID, pData + i, 4);
        DWORD chunkSize = *(DWORD*)(pData + i + 4);

        if (memcmp(chunkID, "data", 4) == 0) {
            audioData = pData + i + 8;
            audioSize = chunkSize;
            break;
        }
        i += 8 + chunkSize;
    }


    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, audioData, audioSize, sampleRate);

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    alSourcei(source, AL_LOOPING, AL_TRUE);
    alSourcePlay(source);

    




	
    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    glfwSetKeyCallback(window.getWindow(), key_callback);
    glfwSetMouseButtonCallback(window.getWindow(), mouse_button_callback);

	AssetManager assetManager;

    Random random;
	
    //Font font = Font(assetManager.getShader("font"), fontTexture);

    assetManager.createMaterial("test");
    Scene scene;

    assetManager.getMaterial("test")->diffuse_texture = assetManager.getTexture("test.png");




    std::vector<Enemy*> enemies;
    std::vector<Bullet*> bullets;
    std::vector<Collectable*> collectable;

    Player player;
    player.setName("player");
    scene.addChild(&player);
    player.bullets = &bullets;

    
    MeshInstance* beerInstance = new MeshInstance("Beer");
    beerInstance->setMesh(assetManager.getMesh("beer.obj"));
    beerInstance->setShader(assetManager.getShader("standart"));
    beerInstance->setMaterial(assetManager.getMaterial("test"));


    MeshInstance* bulletInstance = new MeshInstance("Bullet");
    bulletInstance->setMesh(assetManager.getMesh("bullet.obj"));
    bulletInstance->setShader(assetManager.getShader("standart"));
    bulletInstance->setMaterial(assetManager.getMaterial("test"));



    MeshInstance* enemyInstance = new MeshInstance("Enemy");
    enemyInstance->setMesh(assetManager.getMesh("ship01.obj"));
    enemyInstance->setShader(assetManager.getShader("standart"));
    enemyInstance->setMaterial(assetManager.getMaterial("test"));


    MeshInstance* kimchiInstance = new MeshInstance("Kimchi");
    kimchiInstance->setMesh(assetManager.getMesh("kimchi.obj"));
    kimchiInstance->setShader(assetManager.getShader("standart"));
    kimchiInstance->setMaterial(assetManager.getMaterial("test"));
    

    MeshInstance* meshInstance = new MeshInstance("???");
    meshInstance->setMesh(assetManager.getMesh("ship01.obj"));
    meshInstance->setShader(assetManager.getShader("standart"));
    meshInstance->setMaterial(assetManager.getMaterial("test"));
    scene.addChild(meshInstance);

    MeshInstance* playerInstance = new MeshInstance("Arrow_player");
    playerInstance->setMesh(assetManager.getMesh("player.obj"));
    playerInstance->setShader(assetManager.getShader("standart"));
    playerInstance->setMaterial(assetManager.getMaterial("test"));
    scene.addChild(playerInstance);


    MeshInstance* terrain = new MeshInstance("terrain");
    terrain->setMesh(assetManager.getMesh("terrain.obj"));
    terrain->setShader(assetManager.getShader("standart"));
    terrain->setMaterial(assetManager.getMaterial("test"));
    //scene.addChild(terrain);
    
    Font font(assetManager.getShader("font"), assetManager.getTexture("font.png"));


    
    
    scene.addChild(&camera);

    PlayerController playerController;
    playerController.player = &player;



   

    int spawn_enemy_every = 60;
    int enemy_spawn_countdown = spawn_enemy_every;


    int lives = 3;
    int score = 0;
    int inv = 0;

    const double targetFPS = 60.0;
    const double frameDuration = 1.0 / targetFPS; // 0.01666...


    float kill_hide_countdown = 0;
    float sc = 0;
    float camera_y_st = 0;

    std::string last_killed = "";

    float hard = 1.0;

    float die_countdown = 20.0f;

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

            if (lives < 0 || die_countdown <= 0) {
                break;
            }

            die_countdown -= 0.06;

            hard += 0.0004f;

            playerController.processInput(&window);
           

            camera.projection = glm::perspective(camera.fov / 180.0f * 3.14f, camera.aspectRatio, 0.1f, 5500.0f);
            

            camera_y_st += 0.1;
            player.transform.position.y += 0.1;

            if (player.transform.position.y < camera_y_st) {
                player.transform.position.y = camera_y_st;
            }

            enemy_spawn_countdown -= 1;

            

            if (enemy_spawn_countdown <= 0) {
                enemy_spawn_countdown = spawn_enemy_every / hard;

                Enemy* enemy = new Enemy();

                glm::vec3 dir = glm::vec3(0.0);
                glm::vec2 dir2 = glm::normalize(glm::vec2(player.transform.position.x + (random.randfloat()*3.0-1.5), player.transform.position.y) -
                    glm::vec2(enemy->transform.position.x, enemy->transform.position.y));
                dir.x = dir2.x + (random.randfloat() * 0.5 - 0.25);
                dir.y = -dir2.y;

                enemy->speed = 0.2 * hard;


                enemy->direction = dir;
                enemy->health = hard * 2;
                enemy->countdown_max /= hard * 1;
                enemy->transform = player.transform;
                enemy->transform.position.z = player.transform.position.z;
                enemy->transform.position.x = random.randfloat() * 40.0 - 20;
                enemy->transform.position.y = camera_y_st + 40.0;

                enemies.push_back(enemy);
                
            }

            camera.transform.position = player.transform.position;

            camera.transform.position.x = 0.0f;
            camera.transform.position.z += 30;
            camera.transform.position.y = camera_y_st + 2.0;
            camera.transform.rotation.x = 0.3;

           /* scene.getChild("terrain")->transform = camera.transform;
            scene.getChild("terrain")->transform.position.y += 6;
            scene.getChild("terrain")->transform.position.z -=  40;*/


            
            Actor* actor = scene.getChild("Arrow_player");
            actor->transform = player.transform;
            if (inv > 0) {
                if (inv % 10 == 0) {
                    actor->visible = false;
                }

                if (inv % 15 == 0) {
                    actor->visible = true;
                } 
                
            }
            else {
                actor->visible = true;
            }



            std::unordered_set<Bullet*> deleted_bullets;
            std::unordered_set<Collectable*> deleted_collectables;
            std::unordered_set<Enemy*> deleted_enemies;

            scene.update();
            for (Bullet* bullet : bullets) {
                bullet->update();
                if (bullet->livetime >= 60 * 8) {
                    deleted_bullets.insert(bullet);
                }
            }
            for (Enemy* enemy : enemies) {
                enemy->update();

                if (enemy->livetime >= 60 * 8) {
                    deleted_enemies.insert(enemy);
                    score -= 10;
                }

                if (enemy->countdown <= 0 && enemy->transform.position.y > camera_y_st) {
                    Bullet* bullet = new Bullet();
                    bullet->transform = enemy->transform;
                    enemy->countdown = enemy->countdown_max;
                    bullet->speed = 0.24;
                    bullet->is_enemy = true;
                    glm::vec3 dir = glm::vec3(0.0);
                    glm::vec2 dir2 = glm::normalize(glm::vec2(player.transform.position.x, player.transform.position.y) - 
                        glm::vec2(enemy->transform.position.x, enemy->transform.position.y));
                    dir.x = dir2.x;
                    dir.y = dir2.y;

                    bullet->direction = dir;
                    bullets.push_back(bullet);

                    if (inv < 0) {
                        glm::vec2 delta = enemy->transform.position - player.transform.position;
                        float dist_square = glm::dot(delta, delta);
                        if (dist_square < 4) {
                            lives -= 1;
                            inv = 180;
                        }
                    }
                }

                
            }

            Shader* standart = assetManager.getShader("standart");
            standart->use();
            standart->setMat4("view", camera.view);
            standart->setMat4("projection", camera.projection);

            inv -= 1;

          
            for (Bullet* bullet : bullets) {

                if (!bullet->is_enemy) {
                    for (Enemy* enemy : enemies) {

                        glm::vec2 delta = bullet->transform.position - enemy->transform.position;
                        float dist_square = glm::dot(delta, delta);



                        if (dist_square < enemy->radius * enemy->radius) {
                            deleted_bullets.insert(bullet);
                            enemy->health -= bullet->damage;
                            break;
                        }

   
                        
                    }
                }
                else {
                    if (inv < 0) {
                        glm::vec2 delta = bullet->transform.position - player.transform.position;
                        float dist_square = glm::dot(delta, delta);
                        

                        if (dist_square < 2) {
                            lives -= 1;
                            inv = 180;

                            deleted_bullets.insert(bullet);
                        }


                        

                       
                    }
                }
            }


        


            for (Bullet* bullet : deleted_bullets) {
                bullets.erase(std::remove(bullets.begin(), bullets.end(), bullet), bullets.end());
                delete bullet;
            }


            for (Bullet* bullet : bullets) {
                bulletInstance->transform = bullet->transform;
                bulletInstance->draw();

                bullet->draw();
            }

            kill_hide_countdown -= 1;

            


            for (Collectable *col : collectable) {
                glm::vec2 delta = player.transform.position - col->transform.position;
                float dist_square = glm::dot(delta, delta);
                if (dist_square < 4) {

                    switch (col->type) {
                    case Type::BEER:
                        inv += 40;
                        score += 1000;
                        
                        break;

                    case Type::KIMCHI:
                        lives += 1;
                        score += 1000;
                        break;
                    }

                    deleted_collectables.insert(col);
                }

                col->livetime += 1;

                if (col->livetime > 60 * 10) {
                    deleted_collectables.insert(col);
                }

                switch (col->type) {
                case Type::BEER:
                    beerInstance->transform = col->transform;
                    beerInstance->draw();
                    col->transform.rotation.z += 0.08;
                    break;

                case Type::KIMCHI:
                    kimchiInstance->transform = col->transform;
                    kimchiInstance->draw();
                    col->transform.rotation.z += 0.08;
                    break;
                }
            }
            

    
            for (Enemy* enemy : enemies) {
                if (enemy->health <= 0) {
                    deleted_enemies.insert(enemy);
                    score += enemy->score_kill;
                    last_killed = random.generate_random_name();
                    kill_hide_countdown = 180;
                    die_countdown += 10;
                    sc = (random.randfloat() + 1.0);
                    score += last_killed.size() * 252.0 * sc ;

                    float r = random.randfloat();
                    float r2 = random.randfloat();


                    if (r2 > 0.8) {
                        if (r > 0 && r < 0.9) {
                            Collectable* col = new Collectable();
                            col->type = Type::BEER;
                            col->transform = enemy->transform;
                            collectable.push_back(col);
                            playerController.countdown_max -= 0.5;
                        }

                        if (r > 0.9) {
                            
                            Collectable* col = new Collectable();
                            col->type = Type::KIMCHI;
                            col->transform = enemy->transform;
                            collectable.push_back(col);
                        }
                    }
                }


                enemyInstance->transform = enemy->transform;
                enemyInstance->draw();



                enemy->draw();
            }

            for (Collectable* col : deleted_collectables) {
                collectable.erase(std::remove(collectable.begin(), collectable.end(), col), collectable.end());
                delete col;
            }

            for (Enemy* enemy : deleted_enemies) {
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
                delete enemy;
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

            font.color = glm::vec3(1.0, 1.0, 1.0);
            font.draw(
                "score >" + std::to_string(score) + "\n" +
                "x" + std::to_string(lives) + "\n" +
                "co >" + std::to_string(hard-1.0) + "\n"
                
                , glm::vec2(1.5, logicalHeight - 5.0), &proj);

            font.color = glm::vec3(1.0, 0.0, 0.0);
            if (kill_hide_countdown > 0) {
                font.draw("you killed >" + last_killed + " +" + std::to_string(last_killed.size()*252.0*sc), glm::vec2(1.5, 1.5), &proj);
            }

            font.color = glm::vec3(1.0, 0.0, 0.0);

            font.draw(
                std::to_string(die_countdown) + "\n"

                , glm::vec2(logicalWidth /2, logicalHeight - 3.0), & proj);


            

            glEnable(GL_CULL_FACE);

            glBindVertexArray(0);

            window.swapBuffers();
        }
    }
    glfwTerminate();
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);

    std::cout << "Конец" << "\n";
    std::cout << score << std::endl;

    system("pause");

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