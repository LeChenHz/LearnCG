//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "Shader.h"
//#include "camera.h"
//#include "Model.h"
//#include "texture.h"
//#include "opengl_debug.h"
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// 深度测试
//	glEnable(GL_DEPTH_TEST);
//
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);
//
//	Shader billboardShader("shaders\\billboard\\billboard.vs", "shaders\\billboard\\billboard.fs");
//	Shader cubeShader("shaders\\billboard\\cube.vs", "shaders\\billboard\\cube.fs");
//
//	GLuint billboardTexture = loadDDS("sources\\ExampleBillboard.DDS");
//
//	static const GLfloat g_vertex_buffer_data[] = {
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		-0.5f,  0.5f, 0.0f,
//		0.5f,  0.5f, 0.0f,
//	};
//
//	GLuint billboard_vertex_buffer;
//	glGenBuffers(1, &billboard_vertex_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
//
//	static const GLfloat g_cube_vertex_buffer_data[] = 
//	{ -1.0f,-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f,1.0f, 1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,-1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,-1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f,-1.0f,1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f, 1.0f,-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,-1.0f,-1.0f, 1.0f,
//		1.0f,-1.0f, 1.0f,1.0f, 1.0f, 1.0f,
//		1.0f,-1.0f,-1.0f,1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,1.0f, 1.0f, 1.0f,
//		1.0f,-1.0f, 1.0f,1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f,-1.0f,-1.0f, 1.0f,-1.0f,
//		1.0f, 1.0f, 1.0f,-1.0f, 1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f,1.0f,-1.0f, 1.0f };
//
//	static const GLfloat g_cube_color_buffer_data[] = { 
//		0.583f,  0.771f,  0.014f,0.609f,  0.115f,  0.436f,
//		0.327f,  0.483f,  0.844f,0.822f,  0.569f,  0.201f,
//		0.435f,  0.602f,  0.223f,0.310f,  0.747f,  0.185f,
//		0.597f,  0.770f,  0.761f,0.559f,  0.436f,  0.730f,
//		0.359f,  0.583f,  0.152f,0.483f,  0.596f,  0.789f,
//		0.559f,  0.861f,  0.639f,0.195f,  0.548f,  0.859f,
//		0.014f,  0.184f,  0.576f,0.771f,  0.328f,  0.970f,
//		0.406f,  0.615f,  0.116f,0.676f,  0.977f,  0.133f,
//		0.971f,  0.572f,  0.833f,0.140f,  0.616f,  0.489f,
//		0.997f,  0.513f,  0.064f,0.945f,  0.719f,  0.592f,
//		0.543f,  0.021f,  0.978f,0.279f,  0.317f,  0.505f,
//		0.167f,  0.620f,  0.077f,0.347f,  0.857f,  0.137f,
//		0.055f,  0.953f,  0.042f,0.714f,  0.505f,  0.345f,
//		0.783f,  0.290f,  0.734f,0.722f,  0.645f,  0.174f,
//		0.302f,  0.455f,  0.848f,0.225f,  0.587f,  0.040f,
//		0.517f,  0.713f,  0.338f,0.053f,  0.959f,  0.120f,
//		0.393f,  0.621f,  0.362f,0.673f,  0.211f,  0.457f,
//		0.820f,  0.883f,  0.371f,0.982f,  0.099f,  0.879f };
//
//	GLuint cubevertexbuffer;
//	glGenBuffers(1, &cubevertexbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, cubevertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_vertex_buffer_data), g_cube_vertex_buffer_data, GL_DYNAMIC_DRAW);
//	GLuint cubecolorbuffer;
//	glGenBuffers(1, &cubecolorbuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, cubecolorbuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_cube_color_buffer_data), g_cube_color_buffer_data, GL_DYNAMIC_DRAW);
//
//	// render loop
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		float currentTime = glfwGetTime();
//		deltaTime = currentTime - lastFrame;
//		lastFrame = currentTime;
//
//		// input
//		processInput(window);
//
//		// render
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 ViewMatrix = camera.GetViewMatrix();
//
////绘制箱子
//		glDisable(GL_BLEND);
//		cubeShader.use();
//		glm::mat4 cubeModelMatrix(1.0f);
//		cubeModelMatrix = glm::scale(cubeModelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));
//		glm::mat4 cubeMVP = ProjectionMatrix * ViewMatrix * cubeModelMatrix;
//		cubeShader.setMat4("MVP", cubeMVP);
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, cubevertexbuffer);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, cubecolorbuffer);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
//		glDisableVertexAttribArray(0);
//		glDisableVertexAttribArray(1);
//
//
//// 绘制billboard
//		glm::vec3 CameraPosition = camera.Position;
//		glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
//
//		glEnable(GL_BLEND);
//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		billboardShader.use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, billboardTexture);
//		billboardShader.setInt("myTextureSampler", 0);
//		billboardShader.setVec3("CameraRight_worldspace", ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
//		billboardShader.setVec3("CameraUp_worldspace", ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
//		billboardShader.setVec3("BillboardPos", 0.0f, 0.5f, 0.0f);
//		billboardShader.setVec2("BillboardSize", 1.0f, 0.125f);
//		float LifeLevel = sin(currentTime)*0.1f + 0.7f;
//		billboardShader.setFloat("LifeLevel", LifeLevel);
//		billboardShader.setMat4("VP", ViewProjectionMatrix);
//
//		glEnableVertexAttribArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//		glVertexAttribPointer(
//			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
//			3,                  // size
//			GL_FLOAT,           // type
//			GL_FALSE,           // normalized?
//			0,                  // stride
//			(void*)0            // array buffer offset
//		);
//
//		// 绘制billboard
//		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//		glDisableVertexAttribArray(0);
//
//		glCheckError();
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
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
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
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
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
