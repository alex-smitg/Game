#ifndef GAME_MAIN
#define GAME_MAIN

#include <GL/glew.h>
#include <math.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "glew32s.lib")


#include "Game.h"
#include "asset_manager.h"

int main() {

	AssetManager assetManager;
	assetManager.getMesh("arrow.obj");

	return 0;
}


#endif