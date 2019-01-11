#include "S_MarchingCube.h"



void S_MarchingCube::initGL()
{
	cout << "sizeof(DataType) = " << sizeof(DataType) << endl;
	if (renderWhat == 1)
	{
		target_value = 16.0f;
	}
	else if (renderWhat == 2)
	{
		target_value = 20000; // ��������
		//target_value = 600000; // �������� ��
		//target_value = 400000; // �������� ��
		//target_value = 100.0; //����
		data = new DataType[subdivide_cube_num_x * subdivide_cube_num_y * subdivide_cube_num_z];

		string path("E:\\Desktop\\PET\\ConstructionResult\\pet_raw\\pet_raw1.dat");
		//string path("E:\\Desktop\\PET\\ConstructionResult\\pet_raw\\head.raw");
		readStream = ifstream(path, ifstream::binary);
		if (!readStream)
		{
			cout << "��" << path << "�ļ�ʧ��" << endl;
		}
		readStream.read((char*)data, subdivide_cube_num_x * subdivide_cube_num_y * subdivide_cube_num_z * sizeof(DataType));
	}
	shader = new Shader("shaders/paper/marching_cubes/mc_vs.glsl", "shaders/paper/marching_cubes/mc_fs.glsl");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	marchingCubes();

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * versNumber * 2, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * versNumber, isosurfaceVersPos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * versNumber, sizeof(glm::vec3) * versNumber, isosurfaceVersNormal);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)(sizeof(glm::vec3) * versNumber));
	glEnableVertexAttribArray(1);

	if (paintFrame)
		initCubeFrame(2);

	// ������Ȳ���
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

void S_MarchingCube::paintGL(float deltaTime)
{
	// �����ɫ����Ȼ���
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projection;
	glm::mat4 model;
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.001f, 100.0f);
	shader->setMat4("model_matrix", model);
	shader->setMat4("view_matrix", camera.GetViewMatrix());
	shader->setMat4("projection_matrix", projection);

	if (paintFrame)
		createCubeFrame(2);

	if (first)
	{
		
	}
	first = false;

	shader->use();

	glBindVertexArray(VAO);

	if (g_view_mode == 0)
	{
		glDrawArrays(GL_TRIANGLES, 0, versNumber);
	}
	else if (g_view_mode == 1)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, versNumber);
	}
	else if (g_view_mode == 2)
	{
		shader->setVec3("color", glm::vec3(1.0, 0.0, 0.0));
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_TRIANGLES, 0, versNumber);
		shader->setVec3("color", glm::vec3(1.0, 1.0, 1.0));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, versNumber);
	}

}

void S_MarchingCube::freeGL()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

S_MarchingCube::S_MarchingCube()
{
	hiddenMouse = true;
}


S_MarchingCube::~S_MarchingCube()
{
}

void S_MarchingCube::createCubeFrame(float size)
{
	shader->use();
	glBindVertexArray(FRAME_VAO);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, (void *)0);
}

void S_MarchingCube::initCubeFrame(float size)
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

	glGenVertexArrays(1, &FRAME_VAO);
	glBindVertexArray(FRAME_VAO);

	glGenBuffers(1, &FRAME_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, FRAME_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 24, cube_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &FRAME_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, FRAME_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 24, cube_lines_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	//delete[] cube_vertices;
	//delete[] cube_lines_indices;
}

void S_MarchingCube::marchingCubes()
{
	TestExecutionTime::start();
	versNumber = 0;
	int subdivide_cube_num_max = max(max(subdivide_cube_num_x, subdivide_cube_num_y), subdivide_cube_num_z);
	float step_size = 1.0 / subdivide_cube_num_max;
	// ѭ������ÿ�������壬����������ϸ��������
	for (int i = 0; i < subdivide_cube_num_x-1; ++i)
		for (int j = 0; j < subdivide_cube_num_y-1; ++j)
			for (int k = 0; k < subdivide_cube_num_z-1; ++k)
			{
				marchingCube(i, j, k, step_size, step_size);
			}
	TestExecutionTime::end();
}

void S_MarchingCube::marchingCube(int x_index, int y_index, int z_index, float step_size, float scale)
{
	// �������꣬�����㷨�е�e1-e12���������ֵ��ֱ��ȡ�е�Ļ����ǿ���Ԥ�ȼ���õ�
	glm::vec3 isosurface_vertices_pos[12];
	glm::vec3 isosurface_vertices_normal[12];

	float cube_vertex_value[8]; // cubeÿ�������ֵ
	int cube8_flag_index = 0; // ���cube�Ķ���״̬��flag
	int edge_flag; // ��ȡcube�Ľ���flag
	float a_offset;
	int triangles_num = 0; // cube��Ӧ�������ε�����

	//������
	float x = x_index * step_size, y = y_index * step_size, z = z_index * step_size;
	glm::vec3 subdivie_point = glm::vec3(x, y, z);

	// ��������������cube�����ڱ����ڲ����ⲿ
	for (int i = 0; i < 8; ++i) {
		if (renderWhat == 1) //�����򡣶�̬����cube����ı���ֵ
		{
			//���������ĵ�ľ���
			float distance = glm::distance(subdivie_point + cube_vertex_position[i] * scale, glm::vec3(0.5f, 0.5f, 0.5f));
			cube_vertex_value[i] = 2 / (distance * distance);
		}
		else if(renderWhat == 2) //cube����ı���ֵ��dat���ݻ�ȡ
		{
			int x_offset = 0, y_offset = 0, z_offset = 0;
			//if (i == 1 || i == 2 || i == 5 || i == 6)
			//{
			//	if (x_index != subdivide_cube_num_x - 1)
			//		x_offset = 1;
			//	else { cube_vertex_value[i] = 0; continue; } //�����߽綼���0����
			//}
			//if (i == 2 || i == 3 || i == 6 || i == 7)
			//{
			//	if (y_index != subdivide_cube_num_y - 1)
			//		y_offset = 1;
			//	else { cube_vertex_value[i] = 0; continue; } //�����߽綼���0����
			//}
			//if (i == 4 || i == 5 || i == 6 || i == 7)
			//{
			//	if (z_index != subdivide_cube_num_z - 1)
			//		z_offset = 1;
			//	else { cube_vertex_value[i] = 0; continue; } //�����߽綼���0����
			//}
			x_offset = a2fVertexOffset[i][0];y_offset = a2fVertexOffset[i][1];z_offset = a2fVertexOffset[i][2]; //������ע�͵��Ĵ��빦��һ��
			cube_vertex_value[i] = getDataUseXYZ(data, x_index + x_offset, y_index + y_offset, z_index + z_offset);
		}
		if (cube_vertex_value[i] <= target_value)
			cube8_flag_index |= 1 << i;
	}

	edge_flag = aiCubeEdgeFlags[cube8_flag_index];
	if (edge_flag == 0) { //���û����������Ҫ��
		return;
	}

	for (int i = 0; i < 12; ++i) {
		if (edge_flag & (1 << i)) {
			// cubeһ���ߵ����������ֵ֮��
			float delta = cube_vertex_value[cube_edges_indices[i][1]] - cube_vertex_value[cube_edges_indices[i][0]];
			a_offset = 0.5; //��ֵ����cube�ıߵĽ��㣬ȡcube�ߵ��е�
			if (delta == 0.0)
				a_offset = 0.5;
			else
				a_offset = (target_value - cube_vertex_value[cube_edges_indices[i][0]]) / delta; //������ݱ���ֵ���в�ֵ

			//��ֵ��ÿ�����ϵĽ���
			isosurface_vertices_pos[i].x = x + (cube_vertex_position[cube_edges_indices[i][0]][0]
				+ a_offset * cube_edge_direction[i][0]) * scale;
			isosurface_vertices_pos[i].y = y + (cube_vertex_position[cube_edges_indices[i][0]][1]
				+ a_offset * cube_edge_direction[i][1]) * scale;
			isosurface_vertices_pos[i].z = z + (cube_vertex_position[cube_edges_indices[i][0]][2]
				+ a_offset * cube_edge_direction[i][2]) * scale;
			calVerticesNormal(isosurface_vertices_normal[i], x_index, y_index, z_index);
		}
	}

	for (int i = 0; i < 5; ++i) {
		if (a2iTriangleConnectionTable[cube8_flag_index][3 * i] < 0) // <0 �ȼ��� ==-1
			break;
		triangles_num++;
	}

	//cube��Ӧ�����εıߵ���������
	int triangles_edge_indices_num = triangles_num * 3;

	for (int i = 0; i < triangles_edge_indices_num; ++i)
	{
		isosurfaceVersPos[versNumber] = isosurface_vertices_pos[ a2iTriangleConnectionTable[cube8_flag_index][i] ];
		isosurfaceVersNormal[versNumber] = isosurface_vertices_normal[ a2iTriangleConnectionTable[cube8_flag_index][i]];
		versNumber++;
	}
}

void S_MarchingCube::calVerticesNormal(glm::vec3 & normal, int x_index, int y_index, int z_index)
{
	if ((x_index >= 1 && x_index < subdivide_cube_num_x) &&
		(y_index >= 1 && y_index < subdivide_cube_num_y) &&
		(z_index >= 1 && z_index < subdivide_cube_num_z))
	{
		// ���Ĳ��
		normal.x = getDataUseXYZ(data, x_index + 1, y_index, z_index) - getDataUseXYZ(data, x_index - 1, y_index, z_index);
		normal.y = getDataUseXYZ(data, x_index, y_index + 1, z_index) - getDataUseXYZ(data, x_index, y_index - 1, z_index);
		normal.z = getDataUseXYZ(data, x_index, y_index, z_index + 1) - getDataUseXYZ(data, x_index, y_index, z_index - 1);
		normal = glm::normalize(normal);
	}
}

DataType S_MarchingCube::getDataUseXYZ(DataType *data, int x, int y, int z)
{
	return data[x * subdivide_cube_num_y * subdivide_cube_num_z + y * subdivide_cube_num_z + z];;
}

