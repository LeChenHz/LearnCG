#pragma once

#include "../Scene.h"

#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <mutex>
#include <algorithm>
#include <vector>

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

	GLuint CreateTextureBuffer();
	GLuint CreateTextureBufferEX();

	S_WaterWave();
	~S_WaterWave();

	Shader* shader;
	Shader* computeShader;
	GLuint backendTexture;  //texture
	GLuint anotherTex;
	GLuint computeImageBuffer;
	GLuint VBO, EBO;
	float time = 0.0f;
	bool render = false;
	float of = 0.0f;
	std::deque<ClickEffectParams> drawingElements;
	//std::deque<ClickEffectParams> drawingElements = std::deque<ClickEffectParams>(MAX_DEQUE_SIZE);
	std::mutex Mutex;


};