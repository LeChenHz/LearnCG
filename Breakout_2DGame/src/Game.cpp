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
	Shader shader = ResourceManager::GetInstance()->LoadShader("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl", nullptr, "sprite");
	// вС ср об ио ╫Э т╤
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	shader.use();
	shader.setInt("image", 0);
	shader.setMat4("projection", projection);
	ResourceManager::GetInstance()->LoadTexture("res/awesomeface.png", sprite);
	spriteRenderer = new SpriteRenderer(shader);
}

void Game::ProcessInput(GLfloat dt)
{

}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
	Texture2D texture = ResourceManager::GetInstance()->GetTexture(sprite);
	spriteRenderer->DrawSprite(texture,
		glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
