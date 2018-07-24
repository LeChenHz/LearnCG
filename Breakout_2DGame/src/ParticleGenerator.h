#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>

#include "common/Shader.h"
#include "common/Texture.h"
#include "GameObject.h"

struct Particle {
	glm::vec2 Position, Velocity;
	glm::vec4 Color;
	GLfloat Life;

	Particle(): Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};

class ParticleGenerator
{
public:
	ParticleGenerator(Shader shader, Texture2D texture, GLuint amount);
	void Draw();
	void Update(GLfloat dt, GameObject &object, GLuint newParticles, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
private:
	GLuint amount;
	Shader shader;
	Texture2D texture;
	std::vector<Particle> particles;
	GLuint VAO;
	GLuint lastUsedParticle = 0;
private:
	void init();
	GLuint firstUnusedParticle();
	void respawnParticle(Particle &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

