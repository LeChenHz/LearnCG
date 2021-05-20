#pragma once

#include "../Scene.h"

#include <iostream>
#include <fstream>
#include <string>


class S_MyClickEffect : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL(float deltaTime);
	virtual void freeGL();
	virtual void setCursePos(float x, float y);
	virtual void Clicked() { time = 0.0f; };
	virtual void setRender(bool b) { render = b; };
	virtual void setScreenSize(int width, int height);

	S_MyClickEffect();
	~S_MyClickEffect();

	Shader* shader = nullptr;
	Shader* ClickEffect_1 = nullptr;
	Shader* ClickEffect_2 = nullptr;

	GLuint backendTexture = 0;  //texture
	GLuint effect_1 = 0, effect_2 = 0;
	GLuint texture_target;
	GLuint m_framebuffer = 0;
	GLuint VBO, EBO;
	GLuint effectVBO;
	float time = 0.0f;
	bool render = false;


};