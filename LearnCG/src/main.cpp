#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
using namespace std;

#include "scenes/SceneHead.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height); // ���ڴ�С�����Ļص�����(�����ڴ�С�ı�ʱ���ӿ�ҲҪ�ı�)
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // �����ƻص�
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // ���ֿ��ƻص�
void processInput(GLFWwindow *window); // ���̿��ƻص�
int initGlfw(int width, int height, const char * title, bool hiddenMouse); //��ʼ��Glfw������1����ɹ���0����ʧ��
int initGlad();//��ʼ��Glad������1����ɹ���0����ʧ��

float lastX,lastY;// ��������ʼλ��Ϊ��Ļ����
bool firstMouse = true;

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

GLFWwindow* window; //GL����
Scene *scene;

int main()
{
	scene = new S_MarchingCube();

	if (initGlfw(scene->SCR_WIDTH, scene->SCR_HEIGHT, scene->windowTitle, scene->hiddenMouse) == 0) {
		std::cout << "����GLFW����ʧ��" << std::endl;
		return -1;
	}
	if (initGlad() == 0) {
		std::cout << "��ʼ��Gladʧ��" << std::endl;
		return -1;
	}

	scene->initGL();

	lastX = (float)scene->SCR_WIDTH / 2.0, lastY = (float)scene->SCR_HEIGHT / 2.0;
	lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		// ��ÿһ֡�м�����µ�deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// �������
		processInput(window);
		
		// ����
		scene->paintGL(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	scene->freeGL();
	delete scene;

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		scene->camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	scene->camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scene->camera.ProcessMouseScroll(yoffset);
}

int initGlfw(int width, int height, const char * title, bool hiddenMouse)
{
	// glfw��ʼ�������õ�GL�汾Ϊ3.3���İ汾
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ����GL����
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return 0;
	}

	// ָ��������Ϊ��ǰ����
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	if (hiddenMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // ���ع�꣬���ͣ���ڴ�����
	}
	return 1;
}

int initGlad()
{
	// ��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 0;
	}
	return 1;
}