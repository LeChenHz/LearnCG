#pragma once

#include "../../GL_HEAD.h"
#include <vector>
#include <math.h>

struct Crystal_model {
	glm::vec3 center,
		v1, v2, v3, v4; //���� ���� ���� ����
};

struct DU_model {
	glm::vec3 v1, v2, v3, v4; //���� ���� ���� ����
	std::vector<Crystal_model> CRYSTALs;
};
struct BDM_model {
	glm::vec3 v1,v2, v3, v4, center; //���� ���� ���� ���� ����
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
	float radius; //̽�����뾶
	float BDM_width; //̽��������Ӧ����α߳�
	float BDM_length; // DU_number_perBDM * BDM_width

	int DU_number_perBDM; // ÿ��̽����̽ͷ����
	int Crystall_number_perDU; // ÿ��̽ͷ�����ܶ�

	glm::vec3 center_pos = glm::vec3(0.0f, 0.0f, 0.0f); //�豸���ĵ�
	glm::vec3 up_normal_vec = glm::vec3(0.0, 1.0f, 0.0f); //up��λ����

	std::vector<BDM_model> BDMs;
	std::vector<glm::vec3> vertexs_pos;

private:
	GLuint BDM_VAO, BDM_VBO;
	GLuint DU_VAO, DU_VBO;
	GLfloat *g_bdm_position_data;
	GLfloat *g_du_position_data;
private:
	void init();
public:
	void draw(Shader *shader);
};

