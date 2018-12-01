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
//#include <algorithm> //����
//using namespace std;
//
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
//// ��Ļ����
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
////						 ����
//struct Particle {
//	glm::vec3 pos, speed;
//	unsigned char r, g, b, a; // ��ɫ
//	float size, angle, weight;
//	float life; // ���ӵ�ʣ��������С��0��ʾ����.
//	float cameradistance; // *Squared* ��������ͷ�ľ��壬 ��� dead : -1.0f
//
//	bool operator<(const Particle& that) const {
////		 �������� Զ����������ǰ��
//		return this->cameradistance > that.cameradistance;
//	}
//};
//
//const int MaxParticles = 2000; //���������
//const float spread = 3.0f; //������ɢ�̶�
//const float life = 5.0; //���ӵĴ��ʱ��
//Particle ParticlesContainer[MaxParticles];
//int LastUsedParticle = 0;
//
//// �����������У��ҵ���������������
//int FindUnusedParticle() {
//	for (int i = LastUsedParticle; i<MaxParticles; i++) {
//		if (ParticlesContainer[i].life < 0) {
//			LastUsedParticle = i;
//			return i;
//		}
//	}
//	for (int i = 0; i<LastUsedParticle; i++) {
//		if (ParticlesContainer[i].life < 0) {
//			LastUsedParticle = i;
//			return i;
//		}
//	}
//	return 0;
//}
//
//// ����cameradistance����������
//void SortParticles() {
//	std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
//}
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
//	// ��ɫ��
//	Shader shader("shaders\\particle_system\\particle_system.vs", "shaders\\particle_system\\particle_system.fs");
//
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);
//
//	static GLfloat* g_particule_position_size_data = new GLfloat[MaxParticles * 4];
//	static GLubyte* g_particule_color_data = new GLubyte[MaxParticles * 4];
//	for (int i = 0; i<MaxParticles; i++)
//	{
//		ParticlesContainer[i].life = -1.0f;
//		ParticlesContainer[i].cameradistance = -1.0f;
//	}
//
//	GLuint particleTexture = loadTexture("res\\xuehua.png");
//
//	// ���Ӷ���λ��
//	static const GLfloat g_vertex_buffer_data[] = {
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.5f,  0.5f, 0.0f,
//		0.5f,  0.5f, 0.0f,
//	};
//
//	//  ���ӵĶ������� ��ÿ�����Ӷ�һ����
//	GLuint billboard_vertex_buffer;
//	glGenBuffers(1, &billboard_vertex_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
//
//	//  ���ӵ�λ�úʹ�С
//	GLuint particles_position_buffer;
//	glGenBuffers(1, &particles_position_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);//��ʼ��ΪNULL�������������ӵ����ԣ��������
//
//																							 // ���������ӵ� ��ɫ
//	GLuint particles_color_buffer;
//	glGenBuffers(1, &particles_color_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
//	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);//��ʼ��ΪNULL�������������ӵ����ԣ��������
//
//	lastFrame = glfwGetTime();
//	while (!glfwWindowShouldClose(window))
//	{
//		 //��ÿһ֡�м�����µ�deltaTime
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// �������
//		processInput(window);
//
//		// �����ɫ����Ȼ���
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 ViewMatrix = camera.GetViewMatrix();
//		glm::vec3 CameraPosition = camera.Position;
//		glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
//
//		// �����������ӣ�������������
//		int newparticles = deltaTime / life * MaxParticles;
//
//		for (int i = 0; i<newparticles; i++) {
//			int particleIndex = FindUnusedParticle();
//			ParticlesContainer[particleIndex].life = life;
//			ParticlesContainer[particleIndex].pos = glm::vec3(0, 0, -20.0f); //�������
//			glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f); //��Ҫ����
//															  //��������ķ���ƫ��
//			glm::vec3 randomdir = glm::vec3(
//				(rand() % 2000 - 1000.0f) / 1000.0f, //[-1,1]
//				(rand() % 2000 - 1000.0f) / 1000.0f,
//				(rand() % 2000 - 1000.0f) / 1000.0f
//			);
//
//			ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;
//
//			// �����������ɫ��͸���ȡ���С
//			ParticlesContainer[particleIndex].r = rand() % 256;
//			ParticlesContainer[particleIndex].g = rand() % 256;
//			ParticlesContainer[particleIndex].b = rand() % 256;
//			ParticlesContainer[particleIndex].a = (rand() % 100) + 50;
//			ParticlesContainer[particleIndex].size = (rand() % 1000) / 3000.0f + 0.3f; //[0.3, 0.6]
//		}
//
//		 //ģ�����е�����
//		int ParticlesCount = 0;
//		for (int i = 0; i<MaxParticles; i++) {
//			Particle& p = ParticlesContainer[i]; // ����
//			if (p.life > 0.0f) {
//				p.life -= deltaTime;
//				if (p.life > 0.0f) {
//					// ģ�������Ч����ֻ��������û����ײ
//					p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)deltaTime * 0.5f;
//					p.pos += p.speed * (float)deltaTime;
//					p.cameradistance = glm::length(p.pos - CameraPosition);
//					//�������
//					g_particule_position_size_data[4 * ParticlesCount + 0] = p.pos.x;
//					g_particule_position_size_data[4 * ParticlesCount + 1] = p.pos.y;
//					g_particule_position_size_data[4 * ParticlesCount + 2] = p.pos.z;
//					g_particule_position_size_data[4 * ParticlesCount + 3] = p.size;
//					g_particule_color_data[4 * ParticlesCount + 0] = p.r;
//					g_particule_color_data[4 * ParticlesCount + 1] = p.g;
//					g_particule_color_data[4 * ParticlesCount + 2] = p.b;
//					g_particule_color_data[4 * ParticlesCount + 3] = p.a;
//				}
//				else {
//					//�Ѿ����������ӣ��ڵ���SortParticles()֮�󣬻ᱻ������������
//					p.cameradistance = -1.0f;
//				}
//				ParticlesCount++;
//			}
//		}
//
//		SortParticles();
//
//		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, g_particule_position_size_data);
//
//		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
//		glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, g_particule_color_data);
//
//		//�������
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//		shader.use();
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, particleTexture);
//
//		// ����ͷ���ҷ���
//		shader.setVec3("CameraRight_worldspace", ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
//		// ����ͷ���Ϸ���
//		shader.setVec3("CameraUp_worldspace", ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
//		shader.setMat4("VP", ViewProjectionMatrix);
//
//		// ���ӵĶ�������
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//		glVertexAttribPointer(
//			0,
//			3,
//			GL_FLOAT,
//			GL_FALSE,
//			0,
//			(void*)0
//		);
//
//		// ���ӵ�����λ��
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//		glVertexAttribPointer(
//			1,
//			4,                                // size : x + y + z + size = 4
//			GL_FLOAT,
//			GL_FALSE,
//			0,
//			(void*)0
//		);
//
//		// ���ӵ���ɫ
//		glEnableVertexAttribArray(2);
//		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
//		glVertexAttribPointer(
//			2,
//			4,                                // size : r + g + b + a = 4
//			GL_UNSIGNED_BYTE,
//			GL_TRUE,
//			0,
//			(void*)0
//		);
//
//		glVertexAttribDivisor(0, 0); // ���Ӷ������� : ����������ͬ�� 4 ���������꣬���Եڶ��������� 0
//		glVertexAttribDivisor(1, 1); // ���ӵ�����λ�úʹ�С��ÿһ�����Ӳ�ͬ�����Եڶ��������� 1
//		glVertexAttribDivisor(2, 1); // ���ӵ���ɫ��ÿһ�����Ӳ�ͬ�����Եڶ��������� 1
//
//		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, ParticlesCount);
//
//		glDisableVertexAttribArray(0);
//		glDisableVertexAttribArray(1);
//		glDisableVertexAttribArray(2);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	delete[] g_particule_position_size_data;
//
//	glDeleteBuffers(1, &particles_color_buffer);
//	glDeleteBuffers(1, &particles_position_buffer);
//	glDeleteBuffers(1, &billboard_vertex_buffer);
//	glDeleteProgram(shader.ID);
//	glDeleteTextures(1, &particleTexture);
//	glDeleteVertexArrays(1, &VertexArrayID);
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
