#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

int main12() {
	glm::vec4 vec(1.0f, 0, 0, 1.0f);

	// ±ä»»¾ØÕó
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(2.0f, 0, 0.0f));

	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	return 0;
}