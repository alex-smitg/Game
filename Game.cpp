// Game.cpp : Defines the entry point for the application.
//

#include "Game.h"

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>


#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8
#include <stb_image.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "bullet/btBulletDynamicsCommon.h"


#include "player.h"

#include "shader.h"

#include "game_actor.h"
#include "model_loader.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "image_loader.h"
#include "point_light.h"
#include "rigidbody.h"
#include "obstacle.h"
#include "bulletDebugDraw.h" 

int window_width = 600;
int window_height = 600;
const std::string WINDOW_TITLE = "Game";

float aspectRatio = window_width / window_height;

int fov = 70;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{

	glfwInit();
	std::cout << "Hello" << "\n";

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, WINDOW_TITLE.c_str(), nullptr, nullptr);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}



	std::vector<GameActor*> actors;


	std::vector<std::vector<GLfloat>> vertices;

	std::string assetsPath = std::string(ASSETS_PATH);

	open_obj(assetsPath + "/test.obj", &vertices);

	Shader shader = Shader("standart.vertex", "standart.fragment", true);
	shader.Use();
	glUniform1i(glGetUniformLocation(shader.ID, "oText"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "sText"), 1);
	glUniform1i(glGetUniformLocation(shader.ID, "nText"), 2);

	Texture* diffuse_test = create_texture(assetsPath + "/fabric.png");
	Texture* normal = create_texture(assetsPath + "/fabric_normal.png");
	Texture* spec = create_texture(assetsPath + "/fabric_spec.png");

	Mesh* vg = new Mesh(vertices[0], &shader);

	
	

	Material* mat = new Material();

	vg->material = mat;

	vg->material->diffuse_texture = diffuse_test;
	vg->material->normalmap_texture = normal;
	vg->material->use_normalmap = true;

	vg->material->specular_texture = spec;
	vg->material->use_specular = true;

	vg->material->use_diffuse = true;

	std::vector<PointLight*> lights;

	PointLight* p = new PointLight();

	p->color = glm::vec3(0.0f, 1.0f, 0.0f);
	p->strength = 6.0;
	p->radius = 15.0;
	p->transform.position.y = 3;
		p->transform.position.x = 5;

	PointLight* p2 = new PointLight();

	p2->color = glm::vec3(1.0f, 0.0f, 0.0f);
	p2->strength = 6.0;
	p2->radius = 15.0;

	lights.push_back(p);
	lights.push_back(p2);
	p2->transform.position.y = 6;

	


	float mouse_delta = 0;
	float mouse_old_delta = 0;
	float mouseSpeed = 0.005f;
	bool left_mouse_clicked = false;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 0.55f;

	vg->transform.scale *= 10.0f;
	vg->material->uv_scale = glm::vec2(10.0f, 10.0f);

	//---------------------------PHYSICS--------------------------------------
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
	// The world.
	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));

	BulletDebugDraw* bulletDebugDraw = new BulletDebugDraw();
//
	dynamicsWorld->setDebugDrawer(bulletDebugDraw);
	//---------------------------------------------------------

	dynamicsWorld->getSolverInfo().m_numIterations = 1;
	
	Transform player_transform = Transform();
	player_transform.position.y = 10;
	btCollisionShape* player_collision = new btCapsuleShape(0.7, 1.74f);
	Player* player = new Player(dynamicsWorld, player_collision, 5, player_transform);

	Camera* camera = &player->camera;
	actors.push_back(player);

	btCollisionShape* col_col = new btBoxShape(btVector3(10.0, 0.2, 10.0));
	Obstacle* obs = new Obstacle(dynamicsWorld, col_col, 0);

	obs->mesh = vg;
	actors.push_back(obs);

	

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.2f, 1.0f); //bg color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

			if (left_mouse_clicked == false) {
				left_mouse_clicked = true;
				glfwSetCursorPos(window, window_width / 2, window_height / 2);
			}

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			glfwSetCursorPos(window, window_width / 2, window_height / 2);
			horizontalAngle += mouseSpeed * float(window_width / 2 - xpos);
			verticalAngle += mouseSpeed * float(window_height / 2 - ypos);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
			left_mouse_clicked = false;
		}

		if (verticalAngle < -3.14f / 2.0f) verticalAngle = -3.14f / 2.0f;
		if (verticalAngle > 3.14f / 2.0f) verticalAngle = 3.14f / 2.0f;



		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);

		glm::vec3 up = glm::cross(right, direction);

		glm::vec3 dir = glm::vec3(0.0, 0.0, 0.0);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			dir = (direction * speed );
			
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			dir = -direction * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			dir = right * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			dir = -right * speed;
		}


		player->rigidbody->rigidBody->applyCentralImpulse(btVector3(dir.x, dir.y, dir.z));

		camera->view = glm::lookAt(
			camera->position,           // Camera is here
			camera->position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		dynamicsWorld->stepSimulation(1.0f / 60.0f);
		dynamicsWorld->debugDrawWorld();

		


		glm::mat4 projection(1.0f);
		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 1000.0f);

		shader.Use();
		shader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		shader.setVec3("viewPos", camera->position);
		shader.setMat4("projection", projection);
		shader.setMat4("view", camera->view);



		player->update();

		int n = 0;
		for (PointLight* light : lights) {
			shader.setVec3("pointLights[" + std::to_string(n) + "].position", light->transform.position);
			shader.setVec3("pointLights[" + std::to_string(n) + "].color", light->color);
			shader.setFloat("pointLights[" + std::to_string(n) + "].strength", light->strength);
			shader.setFloat("pointLights[" + std::to_string(n) + "].radius", light->radius);
			n += 1;
		}
		shader.setInt("light_number", n);

		for (GameActor* actor : actors) {
			actor->update();
			actor->draw();
		}




		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}





	glfwTerminate();


	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	//glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
	aspectRatio = (float)width / (float)height;
	if ((int)height == 0) {
		aspectRatio = 1;
	}
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
