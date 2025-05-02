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





#include "shader.h"

#include "game_actor.h"
#include "model_loader.h"
#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "image_loader.h"
#include "point_light.h"
#include "mesh_instance.h"
#include "cell.h"
#include "level_manager.h"
#include "cell_enum.h"
#include "font.h"
#include "font_character.h"

int window_width = 600;
int window_height = 600;
const std::string WINDOW_TITLE = "Game";

float aspectRatio = window_width / window_height;

int fov = 50;


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


	

	std::string assetsPath = std::string(ASSETS_PATH);


	
	//-------------------------SHADERS------------------------------------
	Shader shader = Shader("standart.vertex", "standart.fragment", true);
	shader.Use();
	glUniform1i(glGetUniformLocation(shader.ID, "oText"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "sText"), 1);
	glUniform1i(glGetUniformLocation(shader.ID, "nText"), 2);

	Shader fontShader = Shader("font.vertex", "font.fragment", true);
	fontShader.Use();
	glUniform1i(glGetUniformLocation(shader.ID, "tex"), 0);
	//-------------------------------------------------------------------


	//------------------------TEXTURES-----------------------------------

	Texture* diffuse_test = create_texture(assetsPath + "/fabric.png");
	Texture* normal = create_texture(assetsPath + "/fabric_normal.png");
	Texture* spec = create_texture(assetsPath + "/fabric_spec.png");

	Texture* fontTexture = create_texture(assetsPath + "/font.png");
	//----------------------------------------------------------------

	//------------------------MESH LOADING-------------------------
	std::vector<std::vector<GLfloat>> vertices;
	open_obj(assetsPath + "/cell_walk.obj", &vertices);
	Mesh* cell_walk_mesh = new Mesh(vertices[0], &shader);
	vertices.clear();
	open_obj(assetsPath + "/cell_stand.obj", &vertices);
	Mesh* cell_stand_mesh = new Mesh(vertices[0], &shader);
	//--------------------------------------------------------


	//-------------------------MATERIALS----------------------------
	Material* material = new Material();
	material->use_diffuse = true;
	material->diffuse_texture = diffuse_test;

	cell_stand_mesh->material = material;
	cell_walk_mesh->material = material;
	//---------------------------------------------
	
	//-----------------------LIGTHS--------------------------
	std::vector<PointLight*> lights;

	PointLight* p = new PointLight();

	p->color = glm::vec3(1.0f, 1.0f, 1.0f);
	p->strength = 2.0;
	p->radius = 20.0;
	p->transform.position.y = 5;
	p->transform.position.x = 10;
	p->transform.position.z = 10;
	
	lights.push_back(p);


	PointLight* red = new PointLight();

	red->color = glm::vec3(1.0f, 0.0f, 0.0f);
	lights.push_back(red);

	PointLight* green = new PointLight();
	green->color = glm::vec3(0.0f, 1.0f, 0.0f);
	lights.push_back(green);

	//---------------------------------------------------



	//-------------------FONT-----------------------------
	Font font = Font(&fontShader, fontTexture);
	//-----------------------------------------
	


	float mouse_delta = 0;
	float mouse_old_delta = 0;
	float mouseSpeed = 0.005f;
	bool left_mouse_clicked = false;
	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float speed = 0.05f;



	Camera* camera = new Camera();


	//--------------------------LEVEL-----------------------------

	LevelManager levelManager = LevelManager();

	levelManager.loadLevel(assetsPath + "/level0.map");

	for (int x = 0; x < 9; x++) {
		for (int z = 0; z < 9; z++) {
			Cell* cell = new Cell();
			cell->transform.position.x = x*2;
			cell->transform.position.z = z*2;
			if (levelManager.getCellType(x, z) == CellType::STAND) {
				cell->setMesh(cell_stand_mesh);
			}
			if (levelManager.getCellType(x, z) == CellType::WALK) {
				cell->setMesh(cell_walk_mesh);
			}

			if (levelManager.getCellType(x, z) == CellType::PATH) {
				cell->setMesh(cell_walk_mesh);
			}

			if (levelManager.getCellType(x, z) == CellType::START) {
				cell->setMesh(cell_walk_mesh); //TODO: create new mesh
				red->transform.position = glm::vec3(x, 0.0f, z) * 2.0f;
			}

			if (levelManager.getCellType(x, z) == CellType::END) {
				cell->setMesh(cell_walk_mesh); //TODO: create new mesh
				green->transform.position = glm::vec3(x, 0.0f, z) * 2.0f ;
			}
			
			actors.push_back(cell);
		}
	}

	
	//


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //bg color
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
			camera->position += (direction * speed );
			
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera->position += -direction * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera->position += right * speed;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera->position += -right * speed;
		}



		camera->view = glm::lookAt(
			camera->position,           // Camera is here
			camera->position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		glm::mat4 projection(1.0f);
		projection = glm::perspective(fov / 180.0f * 3.14f, aspectRatio, 0.1f, 500.0f);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
	
		float x = (2.0f * xpos) / window_width - 1.0f;
		float y = 1.0f - (2.0f * ypos) / window_height;


		glm::vec4 screenPos = glm::vec4(x,y , 1.0f, 1.0f);
		glm::mat4 inverseProjection = glm::inverse(projection);
		glm::mat4 inverseView = glm::inverse(camera->view);
		glm::vec4 worldPos = inverseProjection * screenPos;
		worldPos = inverseView * worldPos;
		worldPos /= worldPos.w;


		glm::vec3 rayDirection = glm::normalize(glm::vec3(worldPos) - camera->position);

		float t = -camera->position.y / rayDirection.y; 

		glm::vec3 mouseWorldPos = camera->position + t * rayDirection;
		

		
		

		shader.Use();
		shader.setVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
		shader.setVec3("viewPos", camera->position);
		shader.setMat4("projection", projection);
		shader.setMat4("view", camera->view);



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

		font.draw("hello world\ntesting font\nlol firin my lazor\n.,-+=*/\"'<>()[]!?", glm::vec2(-18.0, -10.6));
		font.color = glm::vec3(1.0, 0.0, 0.0);
		font.draw(std::to_string(glfwGetTime()), glm::vec2(-18.0, 0));
		font.color = glm::vec3(1.0, 1.0, 1.0);

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
