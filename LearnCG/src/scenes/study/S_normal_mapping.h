#pragma once

#include "../Scene.h"

class S_normal_mapping : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL();
	virtual void freeGL();
public:
	S_normal_mapping();
	~S_normal_mapping();
};

