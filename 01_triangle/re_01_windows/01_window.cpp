#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// 初始化glfw
	glfwInit();
	// 告诉glfw我们需要什么版本，什么模式的opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 顶点数据
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // 0
	 0.5f, -0.5f, 0.0f, // 1
	 0.0f,  0.5f, 0.0f, // 2
	 1.0f,  0.5f, 1.0f, // 3
	};
	// 0,1,2   2,1,3两个三角形

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
		std::cout << "窗口创建出错！" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 把window传入上下文,opengl每个时刻只有一个状态机
	glfwMakeContextCurrent(window);

	// 初始化glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew初始化失败" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 定义VAO,VAO里定义了顶点间的关系，以及这些面的法向量，材质uv
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	// 绑定VAO
	glBindVertexArray(VAO);

	// 定义VBO，VBO里存储了我们输入的数据
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// VAO可以绑定两种缓冲类型：VBO和EBO。这里我们绑定VBO，VBO的缓冲类型为GL_ARRAY_BUFFER，因此第一个参数为GL_ARRAY_BUFFER。
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	
	// 将顶点数据输入到VBO中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// 创建EBO,EBO告诉我们每个点的关系
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 创建顶点着色器
	unsigned int vertexShader;
	vertexShader =  glCreateShader(GL_VERTEX_SHADER);
	// 传递Shader代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// 创建片段着色器
	unsigned int fragmentShader;
	fragmentShader =  glCreateShader(GL_FRAGMENT_SHADER);
	// 传递Shader代码
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 将两个Shader组装成shaderProgram才能传给GPU
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
		// 清理颜色缓冲区，并给屏幕glClearColor中的颜色
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


