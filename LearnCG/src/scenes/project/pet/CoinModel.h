#pragma once

#include "../../GL_HEAD.h"
#include "ReadPetBigFile.h"
#include "PetMathmaticalModel.h"

class CoinModel
{
public:
	CoinModel(ReadPetBigFile *readPet, PetMathmaticalModel *petModel);
	~CoinModel();
	void draw(Shader *shader);
public:
	GLuint COIN_VAO, COIN_VBO;
	GLfloat *g_coin_position_data;
	int coinCount;

	Shader *particle_shader;
};

