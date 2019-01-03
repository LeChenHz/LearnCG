#pragma once

#include "../../Scene.h"
#include "PetMathmaticalModel.h"

class S_Pet_Demo : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL(float deltaTime);
	virtual void freeGL();
public:
	S_Pet_Demo();
	~S_Pet_Demo();

public:
	PetMathmaticalModel *perModel;
	Shader *base_shader;
};

