#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	WorldUp = worldup;
	Position = position;
	Forward = glm::normalize(target - position); 
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	WorldUp = worldup;
	Position = position;

	/*Forward.x = glm::cos(pitch) * glm::sin(yaw);  
	Forward.y = glm::sin(pitch);
	Forward.z = glm::cos(pitch) * glm::cos(yaw);*/

	Yaw = yaw;
	Pitch = pitch;

	Forward.x = glm::sin(yaw) * glm::cos(pitch);
	Forward.y = glm::sin(pitch);
	Forward.z = -glm::cos(yaw) * glm::cos(pitch);

	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, Up);
}

void Camera::handleMouseMove(float deltaX, float deltaY)
{
	Pitch += deltaY;
	Yaw += deltaX;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	Forward.x = glm::sin(Yaw) * glm::cos(Pitch);
	Forward.y = glm::sin(Pitch);
	Forward.z = -glm::cos(Yaw) * glm::cos(Pitch);

	Forward = glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
