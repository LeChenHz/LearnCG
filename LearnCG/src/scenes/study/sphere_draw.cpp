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
//// 窗口大小调整的回调函数(当窗口大小改变时，视口也要改变)
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//// 鼠标控制回调
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//// 滚轮控制回调
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//// 键盘控制回调
//void processInput(GLFWwindow *window);
//
//// 屏幕宽，高
//const unsigned int SCR_WIDTH = 720;
//const unsigned int SCR_HEIGHT = 720;
//
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); //摄像机位置
//
//float lastX = (float)SCR_WIDTH / 2.0, lastY = (float)SCR_HEIGHT / 2.0; // 设置鼠标初始位置为屏幕中心
//bool firstMouse = true;
//
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//
//
//void makeSphereVertex();
//
//const GLfloat  PI = 3.14159265358979323846f;
////将球横纵划分成50X50的网格
//const int Y_SEGMENTS = 50;
//const int X_SEGMENTS = 50;
////球的顶点数组
//float SphereVertex[100 * 100 * 5] = {};
//float MiddleVertex[100 * 100 * 5] = {};
//
//
//int main()
//{
//	// ---------------------初始化--------------------------
//	// glfw初始化，采用的GL版本为3.3核心版本
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// 创建GL窗口
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	// 指定上下文为当前窗口
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 隐藏光标，鼠标停留在窗口内
//
//	// 初始化glad
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// 开启深度测试
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//
//	// 着色器
//	Shader shader("shaders\\sphere\\sphere.vs", "shaders\\sphere\\sphere.fs");
//
//	makeSphereVertex();
//
//	// 球
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	//生成并绑定球体的VAO和VBO
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// 将顶点数据转移至GPU中
//	glBufferData(GL_ARRAY_BUFFER, sizeof(MiddleVertex), MiddleVertex, GL_STATIC_DRAW);
//	// 设置顶点属性指针
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// 解绑VAO和VBO
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//
//	lastFrame = glfwGetTime();
//	while (!glfwWindowShouldClose(window))
//	{
//		// 在每一帧中计算出新的deltaTime
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//		// 输入控制
//		processInput(window);
//
//		// 清除颜色和深度缓冲
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		
//		//绘制球
//		//开启面剔除(只需要展示一个面，否则会有重合)
//		glEnable(GL_CULL_FACE); 
//		glCullFace(GL_BACK);
//		glBindVertexArray(VAO);
//		//使用线框模式绘制
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
//	// 球
//	//获取球面上每一点的坐标
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
//	//根据球面上每一点的坐标，去构造一个一个三角形顶点数组
//	int Round = X_SEGMENTS * 3;//SphereVertex每圈的数据个数
//
//	for (unsigned int y = 0; y < (Y_SEGMENTS - 1); ++y)//从第一行的顶点开始，最后一行的顶点不单独绘制三角形
//	{
//		//通过经纬线将球分成一个一个方格，每个方格切分为两个三角形
//		//然后进行顶点赋值，相当于将SphereVertex中每个顶点，扩充成了两个三角形，顶点数为之前的6倍
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