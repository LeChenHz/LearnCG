//
//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
//#include <iostream>
//#include "Shader.h"
//
//#include <iostream>
//#include<fstream>
//using namespace std;
//
//const char *vertexShaderSource = "#version 330 core\n"
//	"layout (location = 0) in vec3 aPos;\n"
//	"layout (location = 1) in vec3 aColor;\n"
//	"out vec3 ourColor;\n"
//	"uniform float xOffset;\n"
//	"void main()\n"
//	"{\n"
//	"   gl_Position = vec4(aPos.x+xOffset, -aPos.y, aPos.z, 1.0);\n"
//	"   ourColor = aColor;\n"
//	"}\0";
//
//const char *fragmentShaderSource = "#version 330 core\n"
//	"out vec4 FragColor;\n"
//	"in vec3 ourColor;\n"
//	"void main()\n"
//	"{\n"
//	"   FragColor = vec4(ourColor, 1.0f);\n"
//	"}\n\0";
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}
//
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, 800, 600);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	//编译顶点着色器
//	unsigned int vertexShader;
//	vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//	glCompileShader(vertexShader);
//	int  success;
//	char infoLog[512];
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//	if (!success)
//	{
//		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	//片段着色器
//	unsigned int fragmentShader;
//	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//	glCompileShader(fragmentShader);
//
//	//着色器程序
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//
//	glUseProgram(shaderProgram);//激活
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	float vertices[] = {
//		// 位置              // 颜色
//		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
//		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部
//	};
//
//	float texCoords[] = {
//		0.0f, 0.0f, // 左下角
//		1.0f, 0.0f, // 右下角
//		0.5f, 1.0f // 上中
//	};
//	
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glUseProgram(shaderProgram);
//
//
//	while (!glfwWindowShouldClose(window))
//	{
//		processInput(window);
//
//		//背景
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		
//		float offset = 0.5f;
//		glUniform1f(glGetUniformLocation(shaderProgram, "xOffset"), offset);
//
//		// render the triangle
//		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	return 1;
//}