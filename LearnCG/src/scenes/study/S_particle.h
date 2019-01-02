#pragma once

#include "../Scene.h"

#include <iostream>
#include <string>
#include <algorithm> //����
using namespace std;

//����
struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a; // ��ɫ
	float size, angle, weight;
	float life; // ���ӵ�ʣ��������С��0��ʾ����.
	float cameradistance; // *Squared* ��������ͷ�ľ��壬 ��� dead : -1.0f

	bool operator<(const Particle& that) const {
		//�������� Զ����������ǰ��
		return this->cameradistance > that.cameradistance;
	}
};

class S_particle : public Scene
{
public:
	virtual void initGL();
	virtual void paintGL(float deltaTime);
	virtual void freeGL();
	S_particle();
	~S_particle();
public:
	int FindUnusedParticle();
	// ����cameradistance����������
	void SortParticles();
public:
	const static int MaxParticles = 2000; //���������
	const float spread = 3.0f; //������ɢ�̶�
	const float life = 5.0; //���ӵĴ��ʱ��
	Particle ParticlesContainer[MaxParticles];
	int LastUsedParticle = 0;

	GLuint VertexArrayID;
	GLfloat* g_particule_position_size_data;
	GLubyte* g_particule_color_data;
	GLuint particleTexture;
	//  ���ӵĶ������� ��ÿ�����Ӷ�һ����
	GLuint billboard_vertex_buffer;
	//  ���ӵ�λ�úʹ�С
	GLuint particles_position_buffer;
	GLuint particles_color_buffer;
	Shader *shader;
};

