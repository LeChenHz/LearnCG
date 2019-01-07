#pragma once

#include "../../GL_HEAD.h"
#include "ReadPetBigFile.h"
#include "PetMathmaticalModel.h"

class CoinModel
{
public:
	CoinModel(ReadPetBigFile *readPet, PetMathmaticalModel *petModel);
	~CoinModel();
	void draw(glm::mat4& projection, glm::mat4& view);
public:
	GLuint COIN_VAO;
	GLuint COIN_VBO;
	GLuint VERTEX_VBO, POS_VBO;
	GLfloat *g_coin_position_data;
	GLfloat *point_position_data;
	int coinCount;
	int pointCount;

	Shader *shader;
	int choice = 0;
};

