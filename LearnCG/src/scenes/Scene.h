#pragma once

#include "GL_HEAD.h"
#include <AntTweakBar/AntTweakBar.h>

#include <iostream>
#include <string>
using namespace std;

#include "../utils/TestExecutionTime.h"

#define MAX_DEQUE_SIZE 12
struct ClickEffectParams
{
	float iTime = 3.0;
	int x = 0;
	int y = 0;
};

class Scene 
{
public:
	virtual void initGL() = 0;
	virtual void paintGL(float deltaTime) = 0; //// deltaTime为两次paint间隔的时间ms
	virtual void freeGL() = 0;
	virtual void initCamera();
	virtual void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	virtual void setCursePos(float x, float y) {};
	virtual void setScreenSize(int width, int height) {};
	virtual void Clicked() {};
	virtual void setRender(bool b) {};
	Scene();

public:
	Camera camera; //摄像机位置

	// 屏幕宽，高
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;

	const char *windowTitle;
	bool hiddenMouse;

public:
	// 用于AntTweakBar
	bool showTwBar = true;
	TwBar *twBar = nullptr;
	void setTwBar(TwBar *bar);
	float mouse_x = -1.0f;
	float mouse_y = -1.0f;

	int m_width = SCR_WIDTH;
	int m_height = SCR_HEIGHT;
};
