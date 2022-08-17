#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// ��ʼ��glfw
	glfwInit();
	// ����glfw������Ҫʲô�汾��ʲôģʽ��opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	float vertices[] = {
	//    ��������    |       ��ɫ       |    ����
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0 ����
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 1 ����
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 2 ����
	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f  // 3 ����
	};
	// 0,1,2   2,1,3����������

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);
	if (!window)
	{
		std::cout << "���ڴ�������" << std::endl;
		glfwTerminate();
		return -1;
	}
	// ��window����������,openglÿ��ʱ��ֻ��һ��״̬��
	glfwMakeContextCurrent(window);

	// ��ʼ��glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew��ʼ��ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}

	Shader myShader = Shader("vertexSource.glsl", "fragmentSource.glsl");

	glViewport(0, 0, 800, 600);

	stbi_set_flip_vertically_on_load(true);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ����VAO,VAO�ﶨ���˶����Ĺ�ϵ���Լ���Щ��ķ�����������uv
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// ��VAO
	glBindVertexArray(VAO);

	// ����VBO��VBO��洢���������������
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// VAO���԰����ֻ������ͣ�VBO��EBO���������ǰ�VBO��VBO�Ļ�������ΪGL_ARRAY_BUFFER����˵�һ������ΪGL_ARRAY_BUFFER��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	// �������������뵽VBO��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// ����EBO,EBO��������ÿ����Ĺ�ϵ
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ��������A
	unsigned int textureBufferA;
	glGenTextures(1, &textureBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBufferA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// ����������ͼ
	int width, height, nrChannel;
	unsigned char* data1 = stbi_load("box.jpg", &width, &height, &nrChannel, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed" << std::endl;
	}
	stbi_image_free(data1);
	data1 = nullptr;

	// ��������B
	unsigned int textureBufferB;
	glGenTextures(1, &textureBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureBufferB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("awesomeface.jpg", &width, &height, &nrChannel, 0);
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed" << std::endl;
	}
	stbi_image_free(data2);
	data2 = nullptr;

	// VAO��������
	// ��һ������ΪVAO�۵�λ�ü�����GLSL��layout��ֵ���ڶ�������Ϊһ�������ɼ�������������Ϊvec3������3��
	// ����������Ϊ������������Ϊfloat�����ĸ�����Ϊ�Ƿ��׼�������Ѿ���׼������false
	// ���������Ϊ��������һ���������ݾ��뿪ͷ���ڵ����ݿ�ͷ�ж�Զ������������Ϊƫ�����������ݴ�ͷ��ʼ��û��ƫ����������ɫ�����ڶ�������֮��������3��floatƫ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ��ɫ��Ϣ
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ������Ϣ
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	myShader.use();
	glUniform1i(glGetUniformLocation(myShader.ID, "box"), 0);
	glUniform1i(glGetUniformLocation(myShader.ID, "smile"), 1);


	// ����任����
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	
	unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		// ������ɫ��������������ĻglClearColor�е���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureBufferB);*/

		/*glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


