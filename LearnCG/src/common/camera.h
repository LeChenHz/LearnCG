#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//��������˶��ļ��ֿ���ѡ���������Զ�봰��ϵͳ�ض������뷽��
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Ĭ�ϵ� camera ֵ
const float YAW = -90.0f; //Ĭ�ϵ�ƫ����
const float PITCH = 0.0f; //Ĭ�ϵĸ�����
const float SPEED = 2.5f; //Ĭ�ϵ��ٶ�
const float SENSITIVITY = 0.1f; //Ĭ�ϵ�������
const float ZOOM = 45.0f; //Ĭ�ϵ��ӽ�

class Camera
{
public:
	glm::vec3 position; //����ͷλ��
	glm::vec3 forward; //����ͷ�ĳ���
	glm::vec3 up; //����ͷ���Ϸ���
	glm::vec3 right; //����ͷ���ҷ���
	glm::vec3 world_up; //����y�᷽��

	float yaw; //ƫ����
	float pitch; //������

	float MovementSpeed;
	float MouseSensitivity;
	float zoom; // �����fov

	// ʹ��������ʼ��
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = YAW, float pitch = PITCH) :
		forward(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->position = position;
		this->world_up = up;
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();

	}

	// ʹ�ñ���ֵ��ʼ��
	Camera(float posX, float posY, float posZ,
		float upX, float upY, float upZ,
		float yaw, float pitch) :
		forward(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->position = glm::vec3(posX, posY, posZ);
		this->world_up = glm::vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();
	}

	// ��ȡ�������View����
	glm::mat4 GetViewMatrix();

	// ���̿����ƶ�
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);

	// �������ӽ�
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// ���ֿ�������
	void ProcessMouseScroll(float yoffset);

	void lookToPos(glm::vec3 lookPos);

private:

	void updateCameraVectors();
	void updateCameraRadius();
};
