#pragma once

#include "../Scene.h"

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <mutex>
#include <algorithm>
#include <vector>

#define MAX_DEQUE_SIZE 12
struct ClickEffectParams
{
	float iTime = 3.0;
	int x = 0;
	int y = 0;
};

class S_WaterWave : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL(float deltaTime);
	virtual void freeGL();
	virtual void setCursePos(float x, float y);
	virtual void Clicked() { time = 0.0f; };
	virtual void setRender(bool b) { render = b; };
	virtual void setScreenSize(int width, int height);

	S_WaterWave();
	~S_WaterWave();

	Shader* shader;
	GLuint backendTexture;  //texture
	GLuint VBO, EBO;
	float time = 0.0f;
	bool render = false;
	std::deque<ClickEffectParams> drawingElements;
	//std::deque<ClickEffectParams> drawingElements = std::deque<ClickEffectParams>(MAX_DEQUE_SIZE);
	std::mutex Mutex;


};