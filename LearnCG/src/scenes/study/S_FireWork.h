#pragma once
#pragma once

#include "../Scene.h"

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <deque>

class S_FireWork : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL(float deltaTime);
	virtual void freeGL();
	virtual void setCursePos(float x, float y);
	virtual void Clicked() { time = 0.9f; };
	virtual void setRender(bool b) { render = b; };

	S_FireWork();
	~S_FireWork();

	Shader* shader;
	GLuint backendTexture;  //texture
	GLuint VBO, EBO;
	float time = 0.0f;
	bool render = false;

	std::deque<ClickEffectParams> drawingElements;
	std::mutex Mutex;


};