#pragma once

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <map>
#include <string>
using namespace std;

class ResourceManager 
{
private:
	static ResourceManager * instance;
public:
	static ResourceManager * GetInstance();
	//map<string, Shader> Shaders;
	map<string, Texture2D> Textures;
	
	//Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	//Shader GetShader(std::string name);
	Texture2D LoadTexture(const GLchar *file, string name);
	Texture2D GetTexture(string name);
	void Clear();
private:
	ResourceManager();
	//Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	Texture2D loadTextureFromFile(const GLchar *path);
};
