#pragma once

#include <glad/glad.h>

#include "GameObject.h"
#include "common/Texture.h"

class BallObject : public GameObject
{
public:
	// ÇòµÄ×´Ì¬
	GLfloat radius;
	GLboolean Stuck;
	GLboolean Sticky, PassThrough;

	BallObject();
	BallObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};

