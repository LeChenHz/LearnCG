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

// ����
enum Direction {
	UP = 0,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;

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
	void KeyDown(int index);
	void KeyUp(int index);
	bool getKeyValue(int index);
	// ������ײ
	void DoCollisions();
	bool CheckCollision(GameObject &one, GameObject &two);
	// Բ��ײ
	Collision CheckCollision(BallObject &one, GameObject &two);
	Direction VectorDirection(glm::vec2 target);
public:
	// �������Ͻ�Ϊ0 0
	GLuint Width, Height;
	// ��Ϸ״̬
	GameState  State;
private:
	bool Keys[1024];
	SpriteRenderer * spriteRenderer;
	vector<GameLevel> Levels;
	GLuint Level;

	GameObject *player;
	BallObject *ball;

	// ��ʼ������Ĵ�С �� ����
	const glm::vec2 PLAYER_SIZE = glm::vec2(100.0f, 20.0f);
	const GLfloat PLAYER_VELOCITY = 500.0f;

	// ��ʼ������ٶ� �� �뾶
	const glm::vec2 INITIAL_BALL_VELOCITY = glm::vec2(100.0f, -350.0f);
	const GLfloat BALL_RADIUS = 12.5f;
};

