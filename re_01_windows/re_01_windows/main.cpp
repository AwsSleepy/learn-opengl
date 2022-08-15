#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

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

	GLFWwindow* window = glfwCreateWindow(800, 600, "HelloWindow", nullptr, nullptr);
	if (!window)
	{
		std::cout << "���ڴ�������" << std::endl;
		glfwTerminate();
		return -1;
	}
	// window����������
	glfwMakeContextCurrent(window);

	// ��ʼ��glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew��ʼ��ʧ��" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glViewport(0, 0, 800, 600);

	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		// ������ɫ��������������ĻglClearColor�е���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

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

void processInput(GLFWwindow* window){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}