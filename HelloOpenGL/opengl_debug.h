#ifndef  OPENGL_DEBUG_H
#define OPENGL_DEBUG_H

#include <glad/glad.h>
#include <string>
#include <iostream>

GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM ö�ٲ������Ϸ�"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE ֵ�������Ϸ�"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION һ��ָ���״̬��ָ��Ĳ������Ϸ�"; break;
		//case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW ѹջ�������ջ����(Overflow)"; break;
		//case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW ��ջ����ʱջ����͵�"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY �ڴ���ò����޷����ã��㹻�ģ��ڴ�"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION ��ȡ��д��һ����������֡����"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

#endif // ! OPENGL_DEBUG_H

