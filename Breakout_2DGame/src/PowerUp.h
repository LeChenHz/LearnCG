#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"

#include <string>

class PowerUp : public GameObject
{
public:
	const glm::vec2 SIZE = glm::vec2(60, 20);
	const glm::vec2 VELOCITY = glm::vec2(0.0f, 150.0f);
	std::string Type;
	GLfloat     Duration;
	GLboolean   Activated;
	PowerUp(std::string type, glm::vec3 color, GLfloat duration, glm::vec2 position, Texture2D texture)
		: GameObject(position, glm::vec2(60, 20), texture, color, glm::vec2(0.0f, 150.0f)), Type(type), Duration(duration), Activated()
	{
	}
};
