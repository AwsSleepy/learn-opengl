#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LightSpot
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);

	float Kc, Kl, Kq; // 衰减系数：常数项，一次项， 平方项

	float cosInnerPhy = 0.99f;    // 内光锥范围
	float cosOutterPhy = 0.95f;  // 外光锥范围

	LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f));
	void UpdateDirection();
};

