#pragma once

#include <vector>
using namespace std;

#include "ResInfo.h"
#include "GameObject.h"
#include "common/ResourceManager.h"

class GameLevel
{
public:
	vector<GameObject> Bricks;
public:
	GameLevel();
	// ���ļ��м��عؿ�
	void Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	// ��Ⱦ�ؿ�
	void Draw(SpriteRenderer &renderer);
	// ���һ���ؿ��Ƿ������ (���зǼ�Ӳ�Ĵ�ש�����ݻ�)
	GLboolean IsCompleted();
private:
	// ��ש�����ݳ�ʼ���ؿ�
	void init(std::vector<vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};

