#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightDirectional
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);

	LightDirectional(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f));
	void UpdateDirection();
};

