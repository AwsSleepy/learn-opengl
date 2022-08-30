#include "Material.h"

Material::Material(Shader* _shader, glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, int _shininess):
	shader(_shader), ambient(_ambient), specular(_specular), shininess(_shininess), diffuse(_diffuse)
{
	
}
