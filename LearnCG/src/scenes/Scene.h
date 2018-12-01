#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../common/Shader.h"
#include "../common/camera.h"
#include "../common/texture.h"
#include "../common/Model.h"

#include <iostream>
#include <string>
using namespace std;

#include "../utils/TestExecutionTime.h"

class Scene {
public:
	virtual void initGL() = 0;
	virtual void paintGL() = 0;
	virtual void freeGL() = 0;

	Scene();

public:
	Camera camera; //ÉãÏñ»úÎ»ÖÃ
	
	// ÆÁÄ»¿í£¬¸ß
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	const char *windowTitle;
	bool hiddenMouse;
};
