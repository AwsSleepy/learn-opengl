#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);

	glm::vec3 Position; // 相机位置
	glm::vec3 Forward;  // 相机目视方向
	glm::vec3 Right;    // 相机右向量
	glm::vec3 Up;       // 相机法向量
	glm::vec3 WorldUp;  // 世界竖直向上的方向

	glm::float32 Pitch, Yaw;
	
	glm::mat4 getViewMatrix();
	void handleMouseMove(float deltaX, float deltaY);
};

