#include "S_MarchingCube_sphere.h"



void S_MarchingCube_sphere::initGL()
{
	shader = new Shader("shaders\\marching_cubes\\mc_vs.glsl", "shaders\\marching_cubes\\mc_fs.glsl");
	if (g_view_mode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void S_MarchingCube_sphere::paintGL(float deltaTime)
{
	// �����ɫ����Ȼ���
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection;
	glm::mat4 model;
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader->setMat4("model_matrix", model);
	shader->setMat4("view_matrix", camera.GetViewMatrix());
	shader->setMat4("projection_matrix", projection);

	if (!onlyFirst)
	{
		createCubeFrame(2);
		marchingCubes();
	} 
	else 
	{
		if (first)
		{
			marchingCubes();
		}
	}
	first = false;


	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * versNumber, iossurfaceVers, GL_STATIC_DRAW);

	shader->use();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);

	glDrawArrays(GL_TRIANGLES, 0, versNumber);

}

void S_MarchingCube_sphere::freeGL()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

S_MarchingCube_sphere::S_MarchingCube_sphere()
{
}


S_MarchingCube_sphere::~S_MarchingCube_sphere()
{
}

void S_MarchingCube_sphere::createCubeFrame(float size)
{
	// ������6����Ķ���
	glm::vec3 *cube_vertices = new glm::vec3[24];
	// ������Ƶ������ζ�������
	unsigned int *cube_lines_indices = new unsigned int[24];
	size *= 0.5;

	int k = 0;
	for (int i = 0; i < 12; ++i) {
		for (int j = 0; j < 2; ++j) {
			cube_vertices[k] = size * cube_vertex_position[cube_edges_indices[i][j]];
			k++;
		}
	}

	k = 0;
	unsigned int j = 0;
	for (unsigned int i = 0; i < 12; ++i) {
		j = i * 2;
		cube_lines_indices[k++] = j;
		cube_lines_indices[k++] = j + 1;
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 24, cube_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 24, cube_lines_indices, GL_STATIC_DRAW);

	shader->use();

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, (void *)0);

	delete[] cube_vertices;
	delete[] cube_lines_indices;
}

void S_MarchingCube_sphere::marchingCubes()
{
	TestExecutionTime::start();
	versNumber = 0;
	float step_size = 1.0 / subdivide_cube_num;
	// ѭ������ÿ�������壬����������ϸ��������
	for (int i = 0; i < subdivide_cube_num; ++i)
		for (int j = 0; j < subdivide_cube_num; ++j)
			for (int k = 0; k < subdivide_cube_num; ++k) {
				//HANDLE handle = GetCurrentProcess();
				//PROCESS_MEMORY_COUNTERS pmc;
				//GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
				marchingCube(i * step_size, j * step_size, k * step_size, step_size);
			}
	TestExecutionTime::end();
}

void S_MarchingCube_sphere::marchingCube(float x, float y, float z, float scale)
{
	glm::vec3 iossurface_vertices[12]; //���ջ��Ƶ������ζ�������
	float cube_vertex_value[8];
	int flag_index = 0; // ���cube�Ķ���״̬��flag
	int edge_flag; // ��ȡcube�Ľ���flag
	float a_offset;
	int triangles_num = 0; // cube��Ӧ�������ε�����

						   //����Դ��
	glm::vec3 source_point = glm::vec3(0.5f, 0.5f, 0.5f);

	//������
	glm::vec3 subdivie_point = glm::vec3(x, y, z);

	// ��������������cube�����ڱ����ڲ����ⲿ
	for (int i = 0; i < 8; ++i) {
		//���������ĵ�ľ���
		float distance = glm::distance(subdivie_point + cube_vertex_position[i] * scale, source_point);
		cube_vertex_value[i] = 2 / (distance * distance);
		if (cube_vertex_value[i] <= target_value)
			flag_index |= 1 << i;
	}

	edge_flag = aiCubeEdgeFlags[flag_index];
	if (edge_flag == 0) { //���û����������Ҫ��
		return;
	}

	for (int i = 0; i < 12; ++i) {
		if (edge_flag & (1 << i)) {
			// cubeһ���ߵ����������ֵ֮��
			float delta = cube_vertex_value[cube_edges_indices[i][1]] - cube_vertex_value[cube_edges_indices[i][0]];
			if (delta == 0.0)
				a_offset = 0.5;
			else
				a_offset = (target_value - cube_vertex_value[cube_edges_indices[i][0]]) / delta;

			//��ֵ��ÿ�����ϵĽ���
			iossurface_vertices[i].x = x + (cube_vertex_position[cube_edges_indices[i][0]][0]
				+ a_offset * cube_edge_direction[i][0]) * scale;
			iossurface_vertices[i].y = y + (cube_vertex_position[cube_edges_indices[i][0]][1]
				+ a_offset * cube_edge_direction[i][1]) * scale;
			iossurface_vertices[i].z = z + (cube_vertex_position[cube_edges_indices[i][0]][2]
				+ a_offset * cube_edge_direction[i][2]) * scale;
		}
	}

	for (int i = 0; i < 5; ++i) {
		if (a2iTriangleConnectionTable[flag_index][3 * i] < 0)
			break;
		triangles_num++;
	}

	//cube��Ӧ�����ε���������
	int triangles_indices_num = triangles_num * 3;

	//cube��Ӧ�����ε�����
	unsigned int triangles_indice;

	for (int i = 0; i < triangles_indices_num; ++i)
	{
		triangles_indice = a2iTriangleConnectionTable[flag_index][i];
		iossurfaceVers[versNumber++] = iossurface_vertices[triangles_indice];
	}
}
