#include "Texture2D.h"

GLuint loadTexture(const char * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	return textureID;
}

Texture2D::Texture2D()
{
	this->Width = 0;
	this->Height = 0;
	this->Internal_Format = GL_RGB;
	this->Image_Format = GL_RGB;
	this->Wrap_S = GL_REPEAT;
	this->Wrap_T = GL_REPEAT;
	//this->Filter_Min = GL_LINEAR_MIPMAP_LINEAR;
	this->Filter_Min = GL_LINEAR;
	this->Filter_Mag = GL_LINEAR;

	glGenTextures(1, &this->ID);
}

void Texture2D::Generate(GLuint width, GLuint height, GLenum format, unsigned char * data)
{
	this->Width = width;
	this->Height = height;
	this->Internal_Format = format;
	this->Image_Format = format;
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Mag);

	// ½â°óÎÆÀí
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
