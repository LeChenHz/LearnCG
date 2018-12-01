//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "common/Shader.h"
//#include "common/camera.h"
//#include "common/texture.h"
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//// ���ڴ�С�����Ļص�����(�����ڴ�С�ı�ʱ���ӿ�ҲҪ�ı�)
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//// �����ƻص�
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//// ���ֿ��ƻص�
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//// ���̿��ƻص�
//void processInput(GLFWwindow *window);
//
//// ��Ļ������
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); //�����λ��
//
//float lastX = (float)SCR_WIDTH / 2.0, lastY = (float)SCR_HEIGHT / 2.0; // ��������ʼλ��Ϊ��Ļ����
//bool firstMouse = true;
//
//float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
//float lastFrame = 0.0f; // ��һ֡��ʱ��
//
//
//
//#define WAVE_COUNT		6
//
//						// ˮ�ĸ߶ȵȼ�
//#define HEIGHT_SCALE 1.6
//
//#define START_X		-4.0
//#define START_Y		-2.5
//#define START_Z		0
//#define LENGTH_X	0.1
//#define LENGTH_Y	0.1
//
//#define STRIP_COUNT		80
//#define STRIP_LENGTH	50
//#define DATA_LENGTH		STRIP_LENGTH*2*(STRIP_COUNT-1)
//
//						//�ṹ��������ʱ���ÿ�����Ĳ��������������Ƶ�ʺ���ʼ����
//static struct {
//	GLfloat time;
//	GLfloat wave_length[WAVE_COUNT], //����
//		wave_height[WAVE_COUNT], //���
//		wave_dir[WAVE_COUNT], //����
//		wave_speed[WAVE_COUNT], //Ƶ��
//		wave_start[WAVE_COUNT * 2]; //��ʼ����
//} values;
//
//static const GLfloat wave_para[6][6] = {
//	//����, ���,   ����,   Ƶ��, ��ʼ����x, ��ʼ����y
//	{ 1.6,	0.12,	0.9,	0.06,	0.0,	0.0 },
//	{ 1.3,	0.1,	1.14,	0.09,	0.0,	0.0 },
//	{ 0.2,	0.01,	0.8,	0.08,	0.0,	0.0 },
//	{ 0.18,	0.008,	1.05,	0.1,	0.0,	0.0 },
//	{ 0.23,	0.005,	1.15,	0.09,	0.0,	0.0 },
//	{ 0.12,	0.003,	0.97,	0.14,	0.0,	0.0 }
//};
//
//static struct {
//	GLuint vertex_buffer, normal_buffer;
//	GLuint vertex_shader, fragment_shader;
//	GLuint diffuse_texture, normal_texture;
//
//	struct {
//		GLint diffuse_texture, normal_texture;
//	} uniforms;
//
//	struct {
//		GLint position;
//		GLint normal;
//	} attributes;
//} names;
//
//// �洢�������� x y z
//static GLfloat pt_strip[STRIP_COUNT*STRIP_LENGTH * 3] = { 0 };
//static GLfloat pt_normal[STRIP_COUNT*STRIP_LENGTH * 3] = { 0 };
//static GLfloat vertex_data[DATA_LENGTH * 3] = { 0 };
//static GLfloat normal_data[DATA_LENGTH * 3] = { 0 };
//
//// ������־���������ֲ�����һ��
//static const GLint gerstner_sort[6] = {
//	0, 0, 1, 1, 1, 1
//};
//
//// ����ϼ⣬��������ϸС��ˮ��
//static const GLfloat gerstner_pt_a[22] = {
//	0.0,0.0, 41.8,1.4, 77.5,5.2, 107.6,10.9,
//	132.4,17.7, 152.3,25.0, 167.9,32.4, 179.8,39.2,
//	188.6,44.8, 195.0,48.5, 200.0,50.0
//};
//// ����Ͽ����������Ʋ����ϳ���ˮ��
//static const GLfloat gerstner_pt_b[22] = {
//	0.0,0.0, 27.7,1.4, 52.9,5.2, 75.9,10.8,
//	97.2,17.6, 116.8,25.0, 135.1,32.4, 152.4,39.2,
//	168.8,44.8, 184.6,48.5, 200.0,50.0
//};
//
//
//static void infoLog(GLuint, PFNGLGETSHADERIVPROC, PFNGLGETSHADERINFOLOGPROC);
//static void initWave(void);
//static float gerstnerZ(float, float, float, const GLfloat *);
//static int normalizeF(float *, float *, int);
//static void calcuWave(void);
//static void initGL(Shader &shader);
//
//
//int main()
//{
//	// ---------------------��ʼ��--------------------------
//	// glfw��ʼ�������õ�GL�汾Ϊ3.3���İ汾
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// ����GL����
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// ָ��������Ϊ��ǰ����
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ���ع�꣬���ͣ���ڴ�����
//
//	// ��ʼ��glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// ������Ȳ���
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//
//
//	// ��ɫ��
//	Shader shader("shaders\\water\\water_vs.glsl", "shaders\\water\\water_fs.glsl");
//	shader.use();
//
//	initWave();
//	initGL(shader);
//
//	lastFrame = glfwGetTime();
//	while (!glfwWindowShouldClose(window))
//	{
//		// ��ÿһ֡�м�����µ�deltaTime
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// �������
//		processInput(window);
//
//		// �����ɫ����Ȼ���
//		glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		calcuWave();
//
//
//		glm::mat4 model(1);
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 ModelViewMat = view * model;
//		glm::mat3 NormalMat = glm::transpose(glm::inverse(glm::mat3(ModelViewMat)));
//		shader.setMat4("modelViewMat", ModelViewMat);
//		shader.setMat4("perspProjMat", projection);
//		shader.setMat3("normalMat", NormalMat);
//
//		shader.setFloat("time", values.time);
//
//		unsigned int VAO;
//		glGenVertexArrays(1, &VAO);
//		glBindVertexArray(VAO);
//
//		glBindBuffer(GL_ARRAY_BUFFER, names.vertex_buffer);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
//		glEnableVertexAttribArray(0);
//
//		glBindBuffer(GL_ARRAY_BUFFER, names.normal_buffer);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(normal_data), normal_data, GL_STATIC_DRAW);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (void*)0);
//		glEnableVertexAttribArray(1);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, names.diffuse_texture);
//
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, names.normal_texture);
//
//		for (int c = 0; c<(STRIP_COUNT - 1); c++)
//			glDrawArrays(GL_TRIANGLE_STRIP, STRIP_LENGTH * 2 * c, STRIP_LENGTH * 2);
//
//		values.time += 0.05;
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//
//
//static void initWave(void)
//{
//	// ��ʼ�� values
//	values.time = 0.0;
//	for (int w = 0; w<WAVE_COUNT; w++)
//	{
//		values.wave_length[w] = wave_para[w][0];
//		values.wave_height[w] = wave_para[w][1];
//		values.wave_dir[w] = wave_para[w][2];
//		values.wave_speed[w] = wave_para[w][3];
//		values.wave_start[w * 2] = wave_para[w][4];
//		values.wave_start[w * 2 + 1] = wave_para[w][5];
//	}
//
//	// ��ʼ�� pt_strip
//	int index = 0;
//	for (int i = 0; i < STRIP_COUNT; i++) //80
//	{
//		for (int j = 0; j < STRIP_LENGTH; j++) //50
//		{
//			pt_strip[index] = START_X + i * LENGTH_X; //-4.0	0.1
//			pt_strip[index + 1] = START_Y + j * LENGTH_Y; //-2.5	0.1
//			index += 3;
//		}
//	}
//}
//
//// �����ڲ庯��
////							  ����			���			 ����λ��			gerstner����
//static float gerstnerZ(float w_length, float w_height, float x_in, const GLfloat gerstner[22])
//{
//	x_in = x_in * 400.0 / w_length;
//
//	while (x_in < 0.0)
//		x_in += 400.0;
//	while (x_in > 400.0)
//		x_in -= 400.0;
//	if (x_in > 200.0)
//		x_in = 400.0 - x_in;
//
//	int i = 0;
//	float yScale = w_height / 50.0;
//	while (i<18 && (x_in<gerstner[i] || x_in >= gerstner[i + 2]))
//		i += 2;
//	if (x_in == gerstner[i])
//		return gerstner[i + 1] * yScale;
//	if (x_in > gerstner[i])
//		return ((gerstner[i + 3] - gerstner[i + 1]) * (x_in - gerstner[i]) / (gerstner[i + 2] - gerstner[i]) + gerstner[i + 3]) * yScale;
//}
//
//// �����淶������
//static int normalizeF(float in[], float out[], int count)
//{
//	int t = 0;
//	float l = 0.0;
//
//	if (count <= 0.0) {
//		printf("normalizeF(): Number of dimensions should be larger than zero.\n");
//		return 1;
//	}
//	while (t<count && in[t]<0.0000001 && in[t]>-0.0000001) {
//		t++;
//	}
//	if (t == count) {
//		printf("normalizeF(): The input vector is too small.\n");
//		return 1;
//	}
//	for (t = 0; t<count; t++)
//		l += in[t] * in[t];
//	//������������ĳ��Ⱥ�С������Ҫ�Ȱ�������������10000�����ٽ��м��㣬�Լ�С���Լ�������Ӱ��
//	if (l < 0.0000001) {
//		l = 0.0;
//		for (t = 0; t<count; t++)
//			in[t] *= 10000.0;
//		for (t = 0; t<count; t++)
//			l += in[t] * in[t];
//	}
//	l = sqrt(l);
//	for (t = 0; t<count; t++)
//		out[t] /= l;
//
//	return 0;
//}
//
//static void calcuWave(void)
//{
//	//����pt_strip[z]����
//	int index = 0;
//	float d, wave;
//	for (int i = 0; i < STRIP_COUNT; i++)
//	{
//		for (int j = 0; j < STRIP_LENGTH; j++)
//		{
//			wave = 0.0;
//			for (int w = 0; w < WAVE_COUNT; w++) {
//				d = (pt_strip[index] - values.wave_start[w * 2] + (pt_strip[index + 1] - values.wave_start[w * 2 + 1]) * tan(values.wave_dir[w]))
//					* cos(values.wave_dir[w]);
//				if (gerstner_sort[w] == 1) {
//					wave += values.wave_height[w] - 
//						gerstnerZ(values.wave_length[w], values.wave_height[w], d + values.wave_speed[w] * values.time, gerstner_pt_a);
//				}
//				else {
//					wave += values.wave_height[w] - 
//						gerstnerZ(values.wave_length[w], values.wave_height[w], d + values.wave_speed[w] * values.time, gerstner_pt_b);
//				}
//			}
//			pt_strip[index + 2] = START_Z + wave * HEIGHT_SCALE;
//			index += 3;
//		}
//	}
//
//	// ���㷨��
//	index = 0;
//	for (int i = 0; i < STRIP_COUNT; i++)
//	{
//		for (int j = 0; j < STRIP_LENGTH; j++)
//		{
//			//  �ϵ�                           �ҵ�            �µ�                           ���
//			int p0 = index - STRIP_LENGTH * 3, p1 = index + 3, p2 = index + STRIP_LENGTH * 3, p3 = index - 3;
//			float xa, ya, za, xb, yb, zb;
//			if (i > 0) {
//				if (j > 0) {
//					xa = pt_strip[p0] - pt_strip[index], ya = pt_strip[p0 + 1] - pt_strip[index + 1], za = pt_strip[p0 + 2] - pt_strip[index + 2];
//					xb = pt_strip[p3] - pt_strip[index], yb = pt_strip[p3 + 1] - pt_strip[index + 1], zb = pt_strip[p3 + 2] - pt_strip[index + 2];
//					pt_normal[index] += ya * zb - yb * za; //���
//					pt_normal[index + 1] += xb * za - xa * zb; //���
//					pt_normal[index + 2] += xa * yb - xb * ya; //���
//				}
//				if (j < STRIP_LENGTH - 1) {
//					xa = pt_strip[p1] - pt_strip[index], ya = pt_strip[p1 + 1] - pt_strip[index + 1], za = pt_strip[p1 + 2] - pt_strip[index + 2];
//					xb = pt_strip[p0] - pt_strip[index], yb = pt_strip[p0 + 1] - pt_strip[index + 1], zb = pt_strip[p0 + 2] - pt_strip[index + 2];
//					pt_normal[index] += ya * zb - yb * za;
//					pt_normal[index + 1] += xb * za - xa * zb;
//					pt_normal[index + 2] += xa * yb - xb * ya;
//				}
//			}
//
//			if (i < STRIP_COUNT - 1) {
//				if (j > 0) {
//					xa = pt_strip[p3] - pt_strip[index], ya = pt_strip[p3 + 1] - pt_strip[index + 1], za = pt_strip[p3 + 2] - pt_strip[index + 2];
//					xb = pt_strip[p2] - pt_strip[index], yb = pt_strip[p2 + 1] - pt_strip[index + 1], zb = pt_strip[p2 + 2] - pt_strip[index + 2];
//					pt_normal[index] += ya * zb - yb * za;
//					pt_normal[index + 1] += xb * za - xa * zb;
//					pt_normal[index + 2] += xa * yb - xb * ya;
//				}
//				if (j < STRIP_LENGTH - 1) {
//					xa = pt_strip[p2] - pt_strip[index], ya = pt_strip[p2 + 1] - pt_strip[index + 1], za = pt_strip[p2 + 2] - pt_strip[index + 2];
//					xb = pt_strip[p1] - pt_strip[index], yb = pt_strip[p1 + 1] - pt_strip[index + 1], zb = pt_strip[p1 + 2] - pt_strip[index + 2];
//					pt_normal[index] += ya * zb - yb * za;
//					pt_normal[index + 1] += xb * za - xa * zb;
//					pt_normal[index + 2] += xa * yb - xb * ya;
//				}
//			}
//
//			if (normalizeF(&pt_normal[index], &pt_normal[index], 3))
//				printf("%d\t%d\n", index / 3 / STRIP_LENGTH, (index / 3) % STRIP_LENGTH);
//
//			index += 3;
//		}
//	}
//
//	// ����pt_strip[]����vertex_data[]������pt_normal[]����normal_data[] 
//	int pt;
//	for (int c = 0; c < (STRIP_COUNT - 1); c++)
//	{
//		for (int l = 0; l < 2 * STRIP_LENGTH; l++)
//		{
//			if (l % 2 == 1) {
//				pt = c * STRIP_LENGTH + l / 2;
//			}
//			else {
//				pt = c * STRIP_LENGTH + l / 2 + STRIP_LENGTH;
//			}
//			index = STRIP_LENGTH * 2 * c + l;
//			for (int i = 0; i<3; i++) {
//				vertex_data[index * 3 + i] = pt_strip[pt * 3 + i];
//				normal_data[index * 3 + i] = pt_normal[pt * 3 + i];
//			}
//		}
//	}
//}
//
//static void initGL(Shader &shader)
//{
//	glClearColor(0.0, 0.0, 0.0, 1.0);
//
//	//�߿�ģʽ
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//	GLfloat materAmbient[] = { 0.1, 0.1, 0.3, 1.0 };
//	GLfloat materSpecular[] = { 0.8, 0.8, 0.9, 1.0 };
//	GLfloat lightDiffuse[] = { 0.7, 0.7, 0.8, 1.0 };
//	GLfloat lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 };
//	GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
//	GLfloat envirAmbient[] = { 0.1, 0.1, 0.3, 1.0 };
//
//	shader.setVec4("materAmbient", materAmbient);
//	shader.setVec4("materSpecular", materSpecular);
//	shader.setVec4("lightDiffuse", lightDiffuse);
//	shader.setVec4("lightAmbient", lightAmbient);
//	shader.setVec4("lightSpecular", lightSpecular);
//	shader.setVec4("envirAmbient", envirAmbient);
//
//	glGenBuffers(1, &names.vertex_buffer);
//	glGenBuffers(1, &names.normal_buffer);
//
//	names.diffuse_texture = loadTexture("res\\water.jpg");
//	names.normal_texture = loadTexture("res\\water_normal.jpg");
//	shader.setFloat("textures[0]", 0);
//	shader.setFloat("textures[1]", 1);
//	
//
//}
//