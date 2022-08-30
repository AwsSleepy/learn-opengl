#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Material
{
public:
	Shader* shader;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 diffuse;
	int shininess;

	Material(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, int shininess);

};

