#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#include "Game.h"
#include "common/ResourceManager.h"

// 屏幕宽高
const GLuint SCREEN_WIDTH = 1280;
const GLuint SCREEN_HEIGHT = 720;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Game breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main()
{
	//初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// 初始化窗口
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BreakOut", NULL, NULL);
	if (window == NULL)
	{
		cout << "打开窗口失败" << endl;
		glfwTerminate();
		while (1);
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// 初始化按键
	glfwSetKeyCallback(window, key_callback);
	// 初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "初始化glad失败" << endl;
		while (1);
		return -1;
	}


	breakout.Init();

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// 检查有没有触发什么事件
		glfwPollEvents();


		breakout.ProcessInput(deltaTime);
		breakout.Update(deltaTime);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		breakout.Render();

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) 
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//TODO
	//if (key >= 0 && key < 1024)
	//{
	//	if (action == GLFW_PRESS)
	//		Breakout.Keys[key] = GL_TRUE;
	//	else if (action == GLFW_RELEASE)
	//		Breakout.Keys[key] = GL_FALSE;
	//}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}