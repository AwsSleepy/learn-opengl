#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color):
	position(_position), angles(_angles), color(_color)
{
	Kc = 1.0f;
	Kl = 0.09f;
	Kq = 0.032f;
}
