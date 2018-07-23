#include "Game.h"

Game::Game(GLuint width, GLuint height)
{
	State = GAME_ACTIVE;
	Width = width;
	Height = height;
}

Game::~Game()
{
	delete spriteRenderer;
}

void Game::Init()
{
	shader = new Shader("shaders\\sprite_vs.glsl", "shaders\\sprite_fs.glsl");
	// вС ср об ио ╫Э т╤
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	shader->setInt("image", 0);
	shader->setMat4("projection", projection);
	ResourceManager::GetInstance()->LoadTexture("res\\awesomeface.png", "face");
	spriteRenderer = new SpriteRenderer(*shader);
}

void Game::ProcessInput(GLfloat dt)
{

}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
	spriteRenderer->DrawSprite(ResourceManager::GetInstance()->GetTexture("face"),
		glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
