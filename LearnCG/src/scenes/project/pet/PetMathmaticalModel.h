#pragma once

#include "../../GL_HEAD.h"
#include <vector>
#include <math.h>

struct Crystal_model {
	glm::vec3 v1, v2, v3, v4, center; //���� ���� ���� ����
};

struct DU_model {
	glm::vec3 v1, v2, v3, v4, center; //���� ���� ���� ����
	std::vector<Crystal_model> CRYSTALs;
};
struct BDM_model {
	glm::vec3 v1,v2, v3, v4, center; //���� ���� ���� ����
	glm::vec3 right_normal_vec; //̽�������ҵ�λ����
	std::vector<DU_model> DUs;
};

class PetMathmaticalModel
{
public:
	PetMathmaticalModel();
	~PetMathmaticalModel();
public:
	int BDM_number; //̽�����ĸ���
	float radius = 10.48f / 2.0f; //̽����ֱ��
	float BDM_width; //̽��������Ӧ����α߳�
	float BDM_length;

	int DU_number = 4; // ̽ͷ����
	int Crystall = 13; //������� 13*13

	glm::vec3 center_pos = glm::vec3(0.0f, 0.0f, 0.0f); //�豸���ĵ�
	glm::vec3 up_normal_vec = glm::vec3(0.0, 1.0f, 0.0f);

	std::vector<BDM_model> BDMs;
	std::vector<glm::vec3> vertexs_pos;

private:
	GLuint VAO, VBO;
	GLfloat *g_bdm_position_data;
	Shader *base_shader;
private:
	void init();
public:
	void draw();
};

