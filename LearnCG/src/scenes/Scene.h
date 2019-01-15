#pragma once

#include "GL_HEAD.h"
#include <AntTweakBar/AntTweakBar.h>

#include <iostream>
#include <string>
using namespace std;

#include "../utils/TestExecutionTime.h"

class Scene 
{
public:
	virtual void initGL() = 0;
	virtual void paintGL(float deltaTime) = 0; //// deltaTimeΪ����paint�����ʱ��ms
	virtual void freeGL() = 0;
	virtual void initCamera();
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	Scene();

public:
	Camera camera; //�����λ��

	// ��Ļ����
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	const char *windowTitle;
	bool hiddenMouse;

public:
	// ����AntTweakBar
	bool showTwBar = true;
	TwBar *twBar = nullptr;
	void setTwBar(TwBar *bar);
};
