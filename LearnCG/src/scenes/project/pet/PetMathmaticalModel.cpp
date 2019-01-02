#include "PetMathmaticalModel.h"

PetMathmaticalModel::PetMathmaticalModel()
{
	BDM_number = 12;
	glm::vec3 v_pos;
	float x, y = 0.0f, z;
	float angle_segment = TWO_PI / BDM_number;
	for (int i = 0; i <= BDM_number; i++)
	{
		float angle = angle_segment * i;
		x = radius * cosf(angle);
		z = radius * sinf(angle);
		v_pos = glm::vec3(x, y, z);
		vertexs_pos.push_back(v_pos);
	}
	BDM_width = glm::distance(vertexs_pos[0], vertexs_pos[1]);
	BDM_length = 4 * BDM_width;

	glm::vec3 y_offset = up_normal_vec * BDM_length / 2.0f;
	for (int i = 0; i < BDM_number; i++)
	{
		BDM_model bdm;
		bdm.center = (vertexs_pos[i] + vertexs_pos[i + 1]) / 2.0f;
		bdm.right_normal_vec = glm::normalize(vertexs_pos[i + 1] - vertexs_pos[i]);
		glm::vec3 xz_offset = bdm.right_normal_vec * BDM_width / 2.0f;
		bdm.v1 = bdm.center - xz_offset + y_offset;
		bdm.v2 = bdm.center + xz_offset + y_offset;
		bdm.v3 = bdm.center + xz_offset - y_offset;
		bdm.v4 = bdm.center - xz_offset - y_offset;
		BDMs.push_back(bdm);
	}

	init();
	draw();
}

PetMathmaticalModel::~PetMathmaticalModel()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete g_bdm_position_data;
	delete base_shader;
}

void PetMathmaticalModel::init()
{
	base_shader = new Shader("shaders/project/pet/base_vs.glsl", "shaders/project/pet/base_fs.glsl");
	g_bdm_position_data = new GLfloat[BDM_number * 6 * 3];
	for (int i = 0; i < BDM_number; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			glm::vec3 v;
			if (j == 0) v = BDMs[i].v1;
			else if (j == 1) v = BDMs[i].v2;
			else if (j == 2) v = BDMs[i].v3;
			else if (j == 3) v = BDMs[i].v1;
			else if (j == 4) v = BDMs[i].v3;
			else if (j == 5) v = BDMs[i].v4;
			g_bdm_position_data[i * 6 * 3 + j * 3 + 0] = v.x;
			g_bdm_position_data[i * 6 * 3 + j * 3 + 1] = v.y;
			g_bdm_position_data[i * 6 * 3 + j * 3 + 2] = v.z;
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_bdm_position_data), g_bdm_position_data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void PetMathmaticalModel::draw()
{
	base_shader->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
