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
	virtual void setCursePos(float x, float y) {};
	virtual void setScreenSize(int width, int height) {};
	virtual void Clicked() {};
	virtual void setRender(bool b) {};
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
	float mouse_x = -1.0f;
	float mouse_y = -1.0f;

	int m_width = SCR_WIDTH;
	int m_height = SCR_HEIGHT;
};
