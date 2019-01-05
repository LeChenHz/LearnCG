#include "CoinModel.h"



CoinModel::CoinModel(ReadPetBigFile *readPet, PetMathmaticalModel *petModel)
{

	particle_shader = new Shader("shaders/project/pet/particle_vs.glsl", "shaders/project/pet/particle_fs.glsl");

	coinCount = readPet->coinCount;

	// coin��Ӧ�ľ�������
	g_coin_position_data = new GLfloat[readPet->coinCount * 3];
	for (int i = 0; i < readPet->coinCount; i++)
	{
		SingleCoin s = readPet->coins[i];
		glm::vec3 v = petModel->BDMs[s.BDMId].DUs[s.DUId].CRYSTALs[s.CrystalId].center;
		g_coin_position_data[i * 3 + 0] = v.x;
		g_coin_position_data[i * 3 + 1] = v.y;
		g_coin_position_data[i * 3 + 2] = v.z;
	}

	glGenVertexArrays(1, &COIN_VAO);
	glGenBuffers(1, &COIN_VBO);
	glBindVertexArray(COIN_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, COIN_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * readPet->coinCount * 3, g_coin_position_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


CoinModel::~CoinModel()
{
}

void CoinModel::draw(Shader *shader)
{
	//���ߵķ�ʽ����coin
	glBindVertexArray(COIN_VAO);
	shader->setVec3("color", 255.0f / 255, 255.0f / 255, 255.0f / 255);
	glDrawArrays(GL_LINES, 0, coinCount / 2);

	////���ƹ���
	//particle_shader->use();
	//// ����ͷ���ҷ���
	//particle_shader->setVec3("CameraRight_worldspace", view[0][0], view[1][0], view[2][0]);
	//// ����ͷ���Ϸ���
	//particle_shader->setVec3("CameraUp_worldspace", view[0][1], view[1][1], view[2][1]);
	//particle_shader->setMat4("VP", projection * view);

}

