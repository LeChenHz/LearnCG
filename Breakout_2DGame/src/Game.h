#pragma once

#include <glad/glad.h>
#include "common/Shader.h"
#include "common/Texture.h"

#include "SpriteRenderer.h"
#include "common/ResourceManager.h"

// ��������Ϸ�ĵ�ǰ״̬
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	Game(GLuint width, GLuint height);
	~Game();

	// ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void Init();
	// ��Ϸѭ��
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
public:
	GLboolean Keys[1024];
	GLuint Width, Height;
	// ��Ϸ״̬
	GameState  State;
private:
	SpriteRenderer * spriteRenderer;
	const string sprite = "face";
};

