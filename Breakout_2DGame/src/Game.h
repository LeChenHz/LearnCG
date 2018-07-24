#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "common/Shader.h"
#include "common/Texture.h"

#include "SpriteRenderer.h"
#include "common/ResourceManager.h"
#include "ResInfo.h"
#include "GameLevel.h"
#include "BallObject.h"

#include <tuple>

// 方向
enum Direction {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

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
	void KeyDown(int index);
	void KeyUp(int index);
	bool getKeyValue(int index);
	// 处理碰撞
	void DoCollisions();
	bool CheckCollision(GameObject &one, GameObject &two);
	// 圆碰撞
	Collision CheckCollision(BallObject &one, GameObject &two);
	Direction VectorDirection(glm::vec2 target);
public:
	// 窗口左上角为0 0
	GLuint Width, Height;
	// 游戏状态
	GameState  State;
private:
	bool Keys[1024];
	SpriteRenderer * spriteRenderer;
	vector<GameLevel> Levels;
	GLuint Level;

	GameObject *player;
	BallObject *ball;

	// 初始化挡板的大小 和 速率
	const glm::vec2 PLAYER_SIZE = glm::vec2(100.0f, 20.0f);
	const GLfloat PLAYER_VELOCITY = 500.0f;

	// 初始化球的速度 和 半径
	const glm::vec2 INITIAL_BALL_VELOCITY = glm::vec2(100.0f, -350.0f);
	const GLfloat BALL_RADIUS = 12.5f;
};

