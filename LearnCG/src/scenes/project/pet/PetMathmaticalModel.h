#pragma once

#include "../../GL_HEAD.h"
#include <vector>
#include <math.h>

struct Crystal_model {
	glm::vec3 v1, v2, v3, v4, center; //左上 右上 右下 左下
};

struct DU_model {
	glm::vec3 v1, v2, v3, v4, center; //左上 右上 右下 左下
	std::vector<Crystal_model> CRYSTALs;
};
struct BDM_model {
	glm::vec3 v1,v2, v3, v4, center; //左上 右上 右下 左下
	glm::vec3 right_normal_vec; //探测器的右单位向量
	std::vector<DU_model> DUs;
};

class PetMathmaticalModel
{
public:
	PetMathmaticalModel();
	~PetMathmaticalModel();
public:
	int BDM_number; //探测器的个数
	float radius = 10.48f / 2.0f; //探测器直径
	float BDM_width; //探测器宽，对应多边形边长
	float BDM_length;

	int DU_number = 4; // 探头个数
	int Crystall = 13; //晶体个数 13*13

	glm::vec3 center_pos = glm::vec3(0.0f, 0.0f, 0.0f); //设备中心点
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

