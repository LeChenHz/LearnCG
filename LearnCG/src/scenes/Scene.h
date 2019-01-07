#pragma once

#include "GL_HEAD.h"

#include <iostream>
#include <string>
using namespace std;

#include "../utils/TestExecutionTime.h"

class Scene {
public:
	virtual void initGL() = 0;
	// deltaTimeΪ����paint�����ʱ��ms
	virtual void paintGL(float deltaTime) = 0;
	virtual void freeGL() = 0;

	Scene();

public:
	Camera camera; //�����λ��
	
	// ��Ļ����
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	const char *windowTitle;
	bool hiddenMouse;
};
