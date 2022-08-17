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

	// ��������
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f, // 1
	 0.0f,  0.5f, 0.0f, // 2
	 1.0f,  0.5f, 1.0f, // 3
	};
	// 0,1,2   2,1,3����������

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 1, 3
	};

	const char* vertexShaderSource = "#version 330 core\n"		 
		"layout (location = 0) in vec3 aPos;\n"					 
		"void main()\n"											 
		"{\n"													 
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	 
		"}\0";													 

	const char* fragmentShaderSource =
		"#version 330 core						  \n"
		"out vec4 FragColor;					  \n"
		"void main()							  \n"
		"{										  \n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}										  \0";

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

	glViewport(0, 0, 800, 600);

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
	// ����������ɫ��
	unsigned int vertexShader;
	vertexShader =  glCreateShader(GL_VERTEX_SHADER);
	// ����Shader����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader =  glCreateShader(GL_FRAGMENT_SHADER);
	// ����Shader����
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// ������Shader��װ��shaderProgram���ܴ���GPU
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		// ������ɫ��������������ĻglClearColor�е���ɫ
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glUseProgram(shaderProgram);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 6);

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


