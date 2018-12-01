#pragma once

#include "Scene.h"

class S_Template : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL();
	virtual void freeGL();
public:
	S_Template();
	~S_Template();
};

