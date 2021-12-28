#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AntTweakBar/AntTweakBar.h>

#include <iostream>
#include <string>
using namespace std;

#include "scenes/SceneHead.h"

#define TWB //##/

void framebuffer_size_callback(GLFWwindow* window, int width, int height); // ���ڴ�С�����Ļص�����(�����ڴ�С�ı�ʱ���ӿ�ҲҪ�ı�)
void mouse_callback(GLFWwindow* window, double xpos, double ypos); // �����ƻص�
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset); // ���ֿ��ƻص�
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void character_callback(GLFWwindow* window, unsigned int codepoint);

void processInput(GLFWwindow *window); // ���̿��ƻص�
int initGlfw(int width, int height, const char * title, bool hiddenMouse); //��ʼ��Glfw������1����ɹ���0����ʧ��
int initGlad();//��ʼ��Glad������1����ɹ���0����ʧ��

float lastX,lastY;// ��������ʼλ��Ϊ��Ļ����
bool firstMouse = true;

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
float totalTime = 0.0f; // ������ʱ��
float mouse_x_pos = 0.0f;
float mouse_y_pos = 0.0f;

GLFWwindow* window; //GL����
Scene *scene;

int main()
{
	scene = new S_WaterWave();
	//scene = new S_FireWork();
	if (initGlfw(scene->SCR_WIDTH, scene->SCR_HEIGHT, scene->windowTitle, scene->hiddenMouse) == 0) {
		std::cout << "����GLFW����ʧ��" << std::endl;
		return -1;
	}
	if (initGlad() == 0) {
		std::cout << "��ʼ��Gladʧ��" << std::endl;
		return -1;
	}

	TwInit(TW_OPENGL_CORE, NULL); // ����ģʽ
	TwWindowSize(scene->SCR_WIDTH, scene->SCR_HEIGHT);

	TwBar *bar;
	
	bar = TwNewBar("Interaction window");

	scene->setTwBar(bar); // Ҫ����scene->initGL()֮ǰ

	//TestExecutionTime::start();
	scene->initGL();
	//TestExecutionTime::end();

	lastX = (float)scene->SCR_WIDTH / 2.0, lastY = (float)scene->SCR_HEIGHT / 2.0;
	glfwSetTime(0);
	float startTime = glfwGetTime();
	
	//int NumberOfExtensions;
	//glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
	//for (int i = 0; i < NumberOfExtensions; i++)
	//{
	//	const GLubyte* ext = glGetStringi(GL_EXTENSIONS, i);
	//	printf("%s \n", ext);
	//}

	while (!glfwWindowShouldClose(window))
	{
		// ��ÿһ֡�м�����µ�deltaTime
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		totalTime += deltaTime;
		//std::cout << totalTime << std::endl;
	
		processInput(window); // �������
		
		scene->paintGL(deltaTime); // ����
		//scene->paintGL(totalTime); // ����

		if(scene->showTwBar)
			//TWB TwDraw();  // ����TweakBar

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	scene->freeGL();
	delete scene;

	TWB TwTerminate(); //�ͷ�TweakBar
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
	//TWB TwWindowSize(width, height);
	scene->setScreenSize(width, height);
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

	mouse_x_pos = xpos;
	mouse_y_pos = ypos;


	scene->camera.ProcessMouseMovement(xoffset, yoffset);
	TWB TwEventMousePosGLFW(xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	scene->camera.ProcessMouseScroll(yoffset);
	TWB TwEventMouseWheelGLFW(yoffset);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(action == GLFW_PRESS)
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			scene->setCursePos(mouse_x_pos, mouse_y_pos);
			scene->Clicked();
			totalTime = 0.9;
			scene->setRender(true);
			break;
		default:
			break;
		}
	TWB TwEventMouseButtonGLFW(button, action);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) //�ص�ԭ��
	{
		scene->initCamera();
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) //���ع��
	{
		scene->hiddenMouse = !scene->hiddenMouse;
		if (scene->hiddenMouse)
			// GLFW_CURSOR_HIDDEN���ع�꣬�����ǻ��Ƴ�GLFW����
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	scene->key_callback(window, key, scancode, action, mods); // �������İ�������
	TWB TwEventKeyGLFW(key, action);
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	TWB TwEventCharGLFW(codepoint, GLFW_PRESS);
}

int initGlfw(int width, int height, const char * title, bool hiddenMouse)
{
	// glfw��ʼ�������õ�GL�汾Ϊ3.3���İ汾
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCharCallback(window, character_callback);
	glfwSetKeyCallback(window, key_callback);


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
