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
	delete player;
	delete ball;
	delete particles;
	delete effects;
}

void Game::Init()
{
	// 加载着色器
	Shader shader = ResourceManager::GetInstance()->LoadShader("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl", nullptr, spriteShaderStr);
	Shader particleShder = ResourceManager::GetInstance()->LoadShader("shaders/particle_vs.glsl", "shaders/particle_fs.glsl", nullptr, particleTextureStr);
	Shader postProcessShader = ResourceManager::GetInstance()->LoadShader("shaders/postprocess_vs.glsl", "shaders/postprocess_fs.glsl", nullptr, postProcessShaderStr);

	// 加载纹理
	ResourceManager::GetInstance()->LoadTexture("res/awesomeface.png", faceTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/block.png", blockTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/block_solid.png", block_solidTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/background.jpg", backgroundTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/paddle.png", paddleTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/particle.png", particleTextureStr);
	ResourceManager::GetInstance()->LoadTexture("res/circle.png", circleTextureStr);

	// 左 右 下 上 近 远 
	// (下 > 上，结果：绘制出来的画面 上下颠倒)
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetInstance()->GetShader(spriteShaderStr).use();
	ResourceManager::GetInstance()->GetShader(spriteShaderStr).setInt("image", 0);
	ResourceManager::GetInstance()->GetShader(spriteShaderStr).setMat4("projection", projection);
	particleShder.use();
	particleShder.setInt("sprite", 0);
	particleShder.setMat4("projection", projection);
	spriteRenderer = new SpriteRenderer(shader);
	particles = new ParticleGenerator(ResourceManager::GetInstance()->GetShader(particleShaderStr), ResourceManager::GetInstance()->GetTexture(particleTextureStr), 500);
	effects = new PostProcessor(postProcessShader, this->Width, this->Height);

	// 加载关卡
	GameLevel one; 
	one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
	GameLevel two; 
	two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
	GameLevel three; 
	three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
	GameLevel four; 
	four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2,this->Height - PLAYER_SIZE.y);
	player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetInstance()->GetTexture(paddleTextureStr));

	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -BALL_RADIUS * 2);
	ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetInstance()->GetTexture(circleTextureStr));

	
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		GLfloat velocity = PLAYER_VELOCITY * dt;
		// 移动玩家挡板
		if (getKeyValue(GLFW_KEY_A) == true || getKeyValue(GLFW_KEY_LEFT) == true)
		{
			if (player->Position.x >= 0)
				player->Position.x -= velocity;
		}
		if (this->Keys[GLFW_KEY_D] == true || getKeyValue(GLFW_KEY_RIGHT) == true)
		{
			if (player->Position.x <= this->Width - player->Size.x)
				player->Position.x += velocity;
		}
		if (this->Keys[GLFW_KEY_SPACE])
			ball->Stuck = false;
	}
}

void Game::Update(GLfloat dt)
{
	ball->Move(dt, this->Width);
	// TODO
	this->DoCollisions();
	particles->Update(dt, *ball, 2, glm::vec2(ball->radius / 2));
	if (ball->Position.y >= this->Height) // 判断球是否接触底部边界
	{
		this->ResetLevel();
		this->ResetPlayer();
	}
	if (ShakeTime > 0.0f)
	{
		ShakeTime -= dt;
		if (ShakeTime <= 0.0f)
			effects->Shake = false;
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		effects->BeginRender();

			Texture2D back = ResourceManager::GetInstance()->GetTexture(backgroundTextureStr);
			// 绘制背景
			spriteRenderer->DrawSprite(back, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
			// 绘制关卡
			this->Levels[this->Level].Draw(*spriteRenderer);
			// 绘制滑板
			player->Draw(*spriteRenderer);
			// 绘制粒子
			particles->Draw();
			// 绘制球
			ball->Draw(*spriteRenderer);

		effects->EndRender();
		effects->Render(glfwGetTime());
	}
}

void Game::KeyDown(int index)
{
	Keys[index] = true;
}

void Game::KeyUp(int index)
{
	Keys[index] = false;
}

bool Game::getKeyValue(int index)
{
	return Keys[index];
}

void Game::DoCollisions()
{
	// 球和砖块的碰撞
	for (GameObject &box : this->Levels[this->Level].Bricks)
	{
		if (!box.Destroyed)
		{
			Collision collision = CheckCollision(*ball, box);
			if (std::get<0>(collision))
			{
				// 如果砖块不是实心就销毁砖块
				if (!box.IsSolid)
					box.Destroyed = GL_TRUE;
				else
				{
					// 如果是实心的砖块则激活shake特效
					ShakeTime = 0.05f;
					effects->Shake = true;
				}
				// 碰撞处理
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT) // 水平方向碰撞
				{
					ball->Velocity.x = -ball->Velocity.x; // 反转水平速度
														  // 重定位
					GLfloat penetration = ball->radius - std::abs(diff_vector.x);
					if (dir == LEFT)
						ball->Position.x += penetration; // 将球右移
					else
						ball->Position.x -= penetration; // 将球左移
				}
				else // 垂直方向碰撞
				{
					ball->Velocity.y = -ball->Velocity.y; // 反转垂直速度
														  // 重定位
					GLfloat penetration = ball->radius - std::abs(diff_vector.y);
					if (dir == UP)
						ball->Position.y -= penetration; // 将球上移
					else
						ball->Position.y += penetration; // 将球下移
				}
			}
		}
	}

	// 球和挡板的冲撞
	Collision result = CheckCollision(*ball, *player);
	if (!ball->Stuck && std::get<0>(result))
	{
		// 检查碰到了挡板的哪个位置，并根据碰到哪个位置来改变速度
		GLfloat centerBoard = player->Position.x + player->Size.x / 2;
		GLfloat distance = (ball->Position.x + ball->radius) - centerBoard;
		GLfloat percentage = distance / (player->Size.x / 2);
		// 依据结果移动
		GLfloat strength = 2.0f;
		glm::vec2 oldVelocity = ball->Velocity;
		ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		ball->Velocity.y = -1 * abs(ball->Velocity.y); //Sticky paddle
		ball->Velocity = glm::normalize(ball->Velocity) * glm::length(oldVelocity);
	}

}

bool Game::CheckCollision(GameObject & one, GameObject & two)
{
	bool collisionX = (one.Position.x + one.Size.x) >= two.Position.x && 
					(two.Position.x + two.Size.x) >= one.Position.x;
	bool collisionY = (one.Position.y + one.Size.y) >= two.Position.y &&
					(two.Position.y + two.Size.y) >= one.Position.y;
	return collisionX && collisionY;
}

Collision Game::CheckCollision(BallObject & one, GameObject & two)
{
	glm::vec2 center(one.Position + one.radius);
	glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
	glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
	// 获取两个中心的差矢量
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// AABB_center加上clamped这样就得到了碰撞箱上距离圆最近的点closest
	glm::vec2 closest = aabb_center + clamped;
	// 获得圆心center和最近点closest的矢量并判断是否 length <= radius
	difference = closest - center;
	if (glm::length(difference) <= one.radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else 
		return std::make_tuple(false, UP, glm::vec2(0, 0));
}

Direction Game::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),  // 上
		glm::vec2(1.0f, 0.0f),  // 右
		glm::vec2(0.0f, -1.0f), // 下
		glm::vec2(-1.0f, 0.0f)  // 左
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}

void Game::ResetLevel()
{
	if (this->Level == 0)
		this->Levels[0].Load("levels/one.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 1)
		this->Levels[1].Load("levels/two.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 2)
		this->Levels[2].Load("levels/three.lvl", this->Width, this->Height * 0.5f);
	else if (this->Level == 3)
		this->Levels[3].Load("levels/four.lvl", this->Width, this->Height * 0.5f);
}

void Game::ResetPlayer()
{
	player->Size = PLAYER_SIZE;
	player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	ball->Reset(player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}

