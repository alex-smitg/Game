//// Game.cpp : Defines the entry point for the application.
////
//
//#include "Game.h"
//
//#include <Windows.h>
//#include <iostream>
//#include <string>
//#include <vector>
//#include <map>
//
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#define STBIW_WINDOWS_UTF8
//#include <stb_image.h>
//
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//
//
//
//
//#include "shader.h"
//
//#include "actor.h"
//#include "model_loader.h"
//#include "shader.h"
//#include "mesh.h"
//#include "camera.h"
//#include "image_loader.h"
//#include "point_light.h"
//#include "mesh_instance.h"
//#include "level_manager.h"
//#include "font.h"
//#include "font_character.h"
//#include "ship.h"
//#include "random.h"
//
//int window_width = 600;
//int window_height = 600;
//const std::string WINDOW_TITLE = "Game";
//
//float aspectRatio = window_width / window_height;
//
//int fov = 40;
//
//bool lclick = false;
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//unsigned int pickingTexture;
//
//int main()
//{
//
//	glfwInit();
//	std::cout << "Hello" << "\n";
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	GLFWwindow* window = glfwCreateWindow(window_width, window_height, WINDOW_TITLE.c_str(), nullptr, nullptr);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//
//	if (window == nullptr)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//
//
//	if (glewInit() != GLEW_OK)
//	{
//		std::cout << "Failed to initialize GLEW" << std::endl;
//		return -1;
//	}
//
//
//
//	std::vector<Actor*> actors;
//
//
//
//
//	std::string assetsPath = std::string(ASSETS_PATH);
//
//	Random random;
//
//	//-------------------------SHADERS------------------------------------
//	Shader shader = Shader("standart.vertex", "standart.fragment", true);
//	shader.Use();
//	glUniform1i(glGetUniformLocation(shader.ID, "oText"), 0);
//	glUniform1i(glGetUniformLocation(shader.ID, "sText"), 1);
//	glUniform1i(glGetUniformLocation(shader.ID, "nText"), 2);
//
//
//	Shader rocketShader = Shader("trail.vertex", "trail.fragment", true);
//
//
//	Shader fontShader = Shader("font.vertex", "font.fragment", true);
//	fontShader.Use();
//	glUniform1i(glGetUniformLocation(shader.ID, "tex"), 0);
//	//-------------------------------------------------------------------
//
//
//	//------------------------TEXTURES-----------------------------------
//
//	Texture* diffuse_test = create_texture(assetsPath + "/fabric.png");
//	Texture* normal = create_texture(assetsPath + "/fabric_normal.png");
//	Texture* spec = create_texture(assetsPath + "/fabric_spec.png");
//
//	Texture* fontTexture = create_texture(assetsPath + "/font.png");
//	//----------------------------------------------------------------
//
//	//------------------------MESH LOADING-------------------------
//	std::vector<std::vector<GLfloat>> vertices;
//	open_obj(assetsPath + "/ship01.obj", &vertices);
//	Mesh* ship01_mesh = new Mesh(vertices[0], &shader);
//
//	vertices.clear();
//	open_obj(assetsPath + "/arrow.obj", &vertices);
//	Mesh* arrow = new Mesh(vertices[0], &shader);
//
//
//	//--------------------------------------------------------
//
//
//	//-------------------------MATERIALS----------------------------
//	Material* material = new Material();
//	material->use_diffuse = true;
//	material->diffuse_texture = diffuse_test;
//
//	ship01_mesh->material = material;
//
//
//
//	Material* green_emission_material = new Material;
//	green_emission_material->emit = true;
//	green_emission_material->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
//
//	arrow->material = green_emission_material;
//	//---------------------------------------------
//
//	//-----------------------LIGTHS--------------------------
//	std::vector<PointLight*> lights;
//
//	PointLight* p = new PointLight();
//
//	p->color = glm::vec3(1.0f, 1.0f, 1.0f);
//	p->strength = 2.0;
//	p->radius = 20.0;
//	p->transform.position.y = 5;
//	p->transform.position.x = 10;
//	p->transform.position.z = 10;
//
//	lights.push_back(p);
//
//
//
//	PointLight* red = new PointLight();
//
//	red->color = glm::vec3(1.0f, 0.0f, 0.0f);
//	lights.push_back(red);
//
//	PointLight* green = new PointLight();
//	green->color = glm::vec3(0.0f, 1.0f, 0.0f);
//	lights.push_back(green);
//
//	Ship* selected = nullptr;
//
//	//---------------------------------------------------
//
//
//	MeshInstance* arrowO = new MeshInstance();
//	arrowO->mesh = arrow;
//
//	actors.push_back(arrowO);
//
//
//	std::map<uint32_t, Ship*> ids;
//
//
//	Ship* player_ship = new Ship();
//	player_ship->meshInstance = new MeshInstance();
//	player_ship->meshInstance->mesh = ship01_mesh;
//	actors.push_back(player_ship);
//	player_ship->name = "babooshka";
//	ids[1] = player_ship;
//	player_ship->id = 1;
//
//
//	for (int i = 2; i < 15; i++) {
//		Ship* _ship = new Ship();
//		_ship->meshInstance = new MeshInstance();
//		_ship->meshInstance->mesh = ship01_mesh;
//		actors.push_back(_ship);
//		_ship->name = random.generate_random_name();
//		_ship->id = i;
//		_ship->is_enemy = true;
//		_ship->transform.position.x = i * 100 * (random.randfloat());
//		_ship->transform.position.z = 100 * (random.randfloat());
//		ids[i] = _ship;
//	}
//	
//	
//
//
//
//
//	std::vector<GameActor*> pickable;
//
//	pickable.push_back(player_ship);
//
//	//-------------------FONT-----------------------------
//	Font font = Font(&fontShader, fontTexture);
//	//-----------------------------------------
//	
//	//-------------------FBO------------------------
//	unsigned int pickingFBO;
//	glGenFramebuffers(1, &pickingFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);
//
//	
//	glGenTextures(1, &pickingTexture);
//	glBindTexture(GL_TEXTURE_2D, pickingTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTexture, 0);
//	//----------------------------------
//
//
//	float mouse_delta = 0;
//	float mouse_old_delta = 0;
//	float mouseSpeed = 0.005f;
//	bool left_mouse_clicked = false;
//	float horizontalAngle = 3.14f;
//	float verticalAngle = 0.0f;
//	float speed = 1.4f;
//
//
//
//	Camera* camera = new Camera();
//
//
//	//--------------------------LEVEL-----------------------------
//
//	LevelManager levelManager = LevelManager();
//
//	levelManager.loadLevel(assetsPath + "/level0.map");
//
//
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //bg color
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
//
//			if (left_mouse_clicked == false) {
//				left_mouse_clicked = true;
//				glfwSetCursorPos(window, window_width / 2, window_height / 2);
//			}
//
//			double xpos, ypos;
//			glfwGetCursorPos(window, &xpos, &ypos);
//			glfwSetCursorPos(window, window_width / 2, window_height / 2);
//			horizontalAngle += mouseSpeed * float(window_width / 2 - xpos);
//			verticalAngle += mouseSpeed * float(window_height / 2 - ypos);
//		}
//		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
//			left_mouse_clicked = false;
//		}
//
//		if (verticalAngle < -3.14f / 2.0f) verticalAngle = -3.14f / 2.0f;
//		if (verticalAngle > 3.14f / 2.0f) verticalAngle = 3.14f / 2.0f;
//
//
//
//		glm::vec3 direction(
//			cos(verticalAngle) * sin(horizontalAngle),
//			sin(verticalAngle),
//			cos(verticalAngle) * cos(horizontalAngle)
//		);
//
//		glm::vec3 right = glm::vec3(
//			sin(horizontalAngle - 3.14f / 2.0f),
//			0,
//			cos(horizontalAngle - 3.14f / 2.0f)
//		);
//
//		glm::vec3 up = glm::cross(right, direction);
//
//		glm::vec3 dir = glm::vec3(0.0, 0.0, 0.0);
//
//		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//			camera->position += (direction * speed );
//			
//		}
//		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//			camera->position += -direction * speed;
//		}
//		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//			camera->position += right * speed;
//		}
//		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//			camera->position += -right * speed;
//		}
//
//
//
//		camera->view = glm::lookAt(
//			camera->position,           // Camera is here
//			camera->position + direction, // and looks here : at the same position, plus "direction"
//			up                  // Head is up (set to 0,-1,0 to look upside-down)
//		);
//
//
//		glm::mat4 projection(1.0f);
//		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 5500.0f);
//
//		double xpos, ypos;
//		glfwGetCursorPos(window, &xpos, &ypos);
//	
//		float x = (2.0f * xpos) / window_width - 1.0f;
//		float y = 1.0f - (2.0f * ypos) / window_height;
//
//
//		glm::vec4 screenPos = glm::vec4(x,y , -1.0f, 1.0f);
//		glm::vec4 rayEye = glm::inverse(projection) * screenPos;
//		rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
//
//		glm::vec4 rayWorld4 = glm::inverse(camera->view) * rayEye;
//		glm::vec3 rayDir = glm::normalize(glm::vec3(rayWorld4));
//
//		glm::vec3 mouseWorldPos  = camera->position + rayDir * 150.0f;
//		
//
//		if (selected == nullptr) {
//			arrowO->visible = false;
//		}
//		else {
//			arrowO->visible = true;
//			arrowO->transform.position = selected->end_pos;
//			arrowO->transform.position.y += 2;
//		}
//		
//		
//		arrowO->transform.scale = glm::vec3(0.3, 0.3, 0.3);
//		arrowO->transform.position.y += sin(glfwGetTime()*2.0) / 3.0;
//		arrowO->transform.rotation.y += 0.01;
//		
//
//		shader.Use();
//		shader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
//		shader.setVec3("viewPos", camera->position);
//		shader.setMat4("projection", projection);
//		shader.setMat4("view", camera->view);
//
//
//
//		int n = 0;
//		for (PointLight* light : lights) {
//			shader.setVec3("pointLights[" + std::to_string(n) + "].position", light->transform.position);
//			shader.setVec3("pointLights[" + std::to_string(n) + "].color", light->color);
//			shader.setFloat("pointLights[" + std::to_string(n) + "].strength", light->strength);
//			shader.setFloat("pointLights[" + std::to_string(n) + "].radius", light->radius);
//			n += 1;
//		}
//		shader.setInt("light_number", n);
//		
//
//		//pick
//		glBindFramebuffer(GL_FRAMEBUFFER, pickingFBO);
//		glClearColor(0, 0, 0, 1);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glViewport(0, 0, window_width, window_height);
//		shader.setBool("color_mode", true);
//
//		for (auto const& [id, ship] : ids)
//		{
//			shader.setVec3("color_color", glm::vec3(id / 255.0f, 0.0, 0.0));
//			ship->draw();
//		}
//
//		unsigned char pixel[3];
//		glReadPixels(xpos, window_height - ypos, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//		uint32_t selectedID = pixel[0];
//
//		if (lclick == true) {
//
//			if (selected == nullptr) {
//				if (ids.count(selectedID)) {
//					selected = ids[selectedID];
//				}
//			}
//
//			else {
//				if (selectedID == 0) {
//					if (selected->can_control == true) {
//						selected->navigate(mouseWorldPos);
//					}
//					else {
//						selected = nullptr;
//					}
//				}
//
//				else {
//					if (selected->can_control == true) {
//						if (selected != ids[selectedID]) {
//							if (ids[selectedID]->is_enemy) {
//								selected->attack(ids[selectedID]);
//							}
//						}
//					}
//				}
//
//			}
//			lclick = false;
//		}
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//		shader.setBool("color_mode", false);
//
//
//
//
//		for (GameActor* actor : actors) {
//			actor->update();
//			actor->draw();
//
//
//
//		}
//
//		shader.Use();
//		shader.setBool("color_mode", true);
//		for (auto const& [id, ship] : ids)
//		{
//			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//			ship->transform.scale += glm::vec3(0.1f, 0.1f, 0.1f);
//
//			if (ship->is_enemy) {
//				shader.setVec3("color_color", glm::vec3(1.0f, 0.0f, 0.0f));
//			}
//			else {
//				shader.setVec3("color_color", glm::vec3(0.0f, 0.2f, 1.0f));
//			}
//
//			if (ship->is_enemy) {
//					ship->next_move += 1;
//
//					if (ship->next_move == 100) {
//						ship->next_move = 0;
//						ship->attack(player_ship);
//				}
//			}
//
//			
//
//
//
//			ship->draw();
//			ship->transform.scale -= glm::vec3(0.1f, 0.1f, 0.1f);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//
//
//			
//
//
//
//
//		}
//		shader.setBool("color_mode", false);
//
//		float logicalWidth = 100.0f; //????
//		float logicalHeight = logicalWidth / aspectRatio;
//
//		glm::mat4 proj = glm::ortho(
//			0.0f, logicalWidth,
//			0.0f, logicalHeight,
//			-1.0f, 1.0f
//		);
//
//
//		glDisable(GL_CULL_FACE);
//
//
//		glClear(GL_DEPTH_BUFFER_BIT);
//		
//		if (selected != nullptr) {
//			font.draw("name > " + selected->name, glm::vec2(1.0, logicalHeight - 1.0f), &proj);
//			font.draw("speed > " + std::to_string(selected->speed * selected->acc), glm::vec2(1.0, logicalHeight - 4.0f), &proj);
//		}
//
//		
//
//		for (auto const& [id, ship] : ids)
//		{
//			fontShader.Use();
//
//			glDisable(GL_CULL_FACE);
//
//			glm::mat4 model = glm::mat4(1.0);
//
//			Transform _temp = ship->transform;
//			_temp.position.y += 1;
//
//
//			float distance = glm::length(camera->position - _temp.position);
//			float scale = distance * 0.004f;
//
//			model = glm::translate(model, _temp.position);
//			model = glm::scale(model, glm::vec3(scale));
//
//			glm::vec3 directionToCamera = glm::normalize(camera->position - glm::vec3(model[3][0], model[3][1], model[3][1]));
//			float angle = atan2(directionToCamera.x, directionToCamera.z);
//			glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
//
//			model = model * rotationMatrix;
//
//			fontShader.setBool("in_world", true);
//			fontShader.setMat4("model", model);
//			fontShader.setMat4("view", camera->view);
//			font.draw(ship->name +"\n"+std::to_string(ship->health) , glm::vec2(0.0, 0.0), &projection);
//			fontShader.setBool("in_world", false);
//
//
//			glEnable(GL_CULL_FACE);
//		}
//
//
//		font.color = glm::vec3(1.0, 0.0, 0.0);
//		font.draw(std::to_string(glfwGetTime()), glm::vec2(glfwGetTime(), glfwGetTime()), &proj);
//		font.color = glm::vec3(1.0, 1.0, 1.0);
//
//		
//
//		glEnable(GL_CULL_FACE);
//
//		glBindVertexArray(0);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//
//
//
//
//	glfwTerminate();
//
//
//	return 0;
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//
//	//glViewport(0, 0, width, height);
//	window_width = width;
//	window_height = height;
//	aspectRatio = (float)width / (float)height;
//	if ((int)height == 0) {
//		aspectRatio = 1;
//	}
//	glBindTexture(GL_TEXTURE_2D, pickingTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, window_width, window_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == 0) {
//		lclick = true;
//	}
//
//
//	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == 1) {
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	}
//	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == 0) {
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//	}
//
//}
