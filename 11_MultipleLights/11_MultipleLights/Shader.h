#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID; // ShaderProgram ID

	void use();
	void setUniform3f(const char* paraNameString, glm::vec3 param);
	void setUniform1i(const char* paraNameString, int param);

private:
	void checkCompileErrors(unsigned int ID, std::string type);
};

