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
//// ��Ļ����
//const unsigned int SCR_WIDTH = 720;
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
//void makeSphereVertex();
//
//const GLfloat  PI = 3.14159265358979323846f;
////������ݻ��ֳ�50X50������
//const int Y_SEGMENTS = 50;
//const int X_SEGMENTS = 50;
////��Ķ�������
//float SphereVertex[100 * 100 * 5] = {};
//float MiddleVertex[100 * 100 * 5] = {};
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
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ���ع�꣬���ͣ���ڴ�����
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
//	Shader shader("shaders\\sphere\\sphere.vs", "shaders\\sphere\\sphere.fs");
//
//	makeSphereVertex();
//
//	// ��
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	//���ɲ��������VAO��VBO
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// ����������ת����GPU��
//	glBufferData(GL_ARRAY_BUFFER, sizeof(MiddleVertex), MiddleVertex, GL_STATIC_DRAW);
//	// ���ö�������ָ��
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// ���VAO��VBO
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
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
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		
//		//������
//		//�������޳�(ֻ��Ҫչʾһ���棬��������غ�)
//		glEnable(GL_CULL_FACE); 
//		glCullFace(GL_BACK);
//		glBindVertexArray(VAO);
//		//ʹ���߿�ģʽ����
//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		glDrawArrays(GL_TRIANGLES, 0, X_SEGMENTS*Y_SEGMENTS * 6);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//void makeSphereVertex()
//{
//	// ��
//	//��ȡ������ÿһ�������
//	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//	{
//		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//		{
//			float xSegment = (float)x / (float)X_SEGMENTS;
//			float ySegment = (float)y / (float)Y_SEGMENTS;
//			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//			float yPos = std::cos(ySegment * PI);
//			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//			SphereVertex[X_SEGMENTS*y * 3 + x * 3] = xPos;
//			SphereVertex[X_SEGMENTS*y * 3 + x * 3 + 1] = yPos;
//			SphereVertex[X_SEGMENTS*y * 3 + x * 3 + 2] = zPos;
//		}
//	}
//
//	//����������ÿһ������꣬ȥ����һ��һ�������ζ�������
//	int Round = X_SEGMENTS * 3;//SphereVertexÿȦ�����ݸ���
//
//	for (unsigned int y = 0; y < (Y_SEGMENTS - 1); ++y)//�ӵ�һ�еĶ��㿪ʼ�����һ�еĶ��㲻��������������
//	{
//		//ͨ����γ�߽���ֳ�һ��һ������ÿ�������з�Ϊ����������
//		//Ȼ����ж��㸳ֵ���൱�ڽ�SphereVertex��ÿ�����㣬����������������Σ�������Ϊ֮ǰ��6��
//		for (unsigned int x = 0; x < X_SEGMENTS; ++x)
//		{
//			long int temp = X_SEGMENTS * y * 3 + x * 3;
//			long int MiddleTemp = (X_SEGMENTS*(y) * 18 + x * 18);
//			MiddleVertex[MiddleTemp] = SphereVertex[temp + Round];
//			MiddleVertex[MiddleTemp + 1] = SphereVertex[temp + 1 + Round];
//			MiddleVertex[MiddleTemp + 2] = SphereVertex[temp + 2 + Round];
//
//			MiddleVertex[MiddleTemp + 3] = SphereVertex[temp];
//			MiddleVertex[MiddleTemp + 4] = SphereVertex[temp + 1];
//			MiddleVertex[MiddleTemp + 5] = SphereVertex[temp + 2];
//
//			MiddleVertex[MiddleTemp + 6] = SphereVertex[temp + 3];
//			MiddleVertex[MiddleTemp + 7] = SphereVertex[temp + 4];
//			MiddleVertex[MiddleTemp + 8] = SphereVertex[temp + 5];
//
//			MiddleVertex[MiddleTemp + 9] = SphereVertex[temp + Round];
//			MiddleVertex[MiddleTemp + 10] = SphereVertex[temp + 1 + Round];
//			MiddleVertex[MiddleTemp + 11] = SphereVertex[temp + 2 + Round];
//
//			MiddleVertex[MiddleTemp + 12] = SphereVertex[temp + 3];
//			MiddleVertex[MiddleTemp + 13] = SphereVertex[temp + 4];
//			MiddleVertex[MiddleTemp + 14] = SphereVertex[temp + 5];
//
//			MiddleVertex[MiddleTemp + 15] = SphereVertex[temp + 3 + Round];
//			MiddleVertex[MiddleTemp + 16] = SphereVertex[temp + 4 + Round];
//			MiddleVertex[MiddleTemp + 17] = SphereVertex[temp + 5 + Round];
//		}
//
//	}
//
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