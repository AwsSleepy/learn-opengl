#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position), angles(_angles), color(_color)
{
	Kc = 1.0f;
	Kl = 0.3f;
	Kq = 0.032f;
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	glm::mat4 rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(angles.z), glm::vec3(0, 0, 1.0f));
	rotate = glm::rotate(rotate, glm::radians(angles.x), glm::vec3(1.0f, 0, 0));
	rotate = glm::rotate(rotate, glm::radians(angles.y), glm::vec3(0, 1.0f, 0));
	glm::mat3 r = {
		rotate[0][0], rotate[0][1], rotate[0][2],
		rotate[1][0], rotate[1][1], rotate[1][2],
		rotate[2][0], rotate[2][1], rotate[2][2]
	};
	direction = -(r * direction);
}
