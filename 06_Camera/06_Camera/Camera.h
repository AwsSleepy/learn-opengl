#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);

	glm::vec3 Position; // ���λ��
	glm::vec3 Forward;  // ���Ŀ�ӷ���
	glm::vec3 Right;    // ���������
	glm::vec3 Up;       // ���������
	glm::vec3 WorldUp;  // ������ֱ���ϵķ���

	glm::float32 Pitch, Yaw;
	
	glm::mat4 getViewMatrix();
	void handleMouseMove(float deltaX, float deltaY);
};

