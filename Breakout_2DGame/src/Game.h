#pragma once

#include <glad/glad.h>
#include "common/Shader.h"
#include "common/Texture.h"

#include "SpriteRenderer.h"
#include "common/ResourceManager.h"

// 代表了游戏的当前状态
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

	// 初始化游戏状态（加载所有的着色器/纹理/关卡）
	void Init();
	// 游戏循环
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
public:
	GLboolean Keys[1024];
	GLuint Width, Height;
	// 游戏状态
	GameState  State;
private:
	SpriteRenderer * spriteRenderer;
	const string sprite = "face";
};

