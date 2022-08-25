#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera* camera);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// 定义摄像机类
// Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));

int main()
{
	// 初始化glfw
	glfwInit();
	// 告诉glfw我们需要什么版本，什么模式的opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 顶点数据
	//float vertices[] = {
	////    顶点坐标    |       颜色       |    纹理
	//-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 0 左下
	// 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 1 右下
	//-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 2 左上
	// 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f  // 3 右上
	//};
	// 0,1,2   2,1,3两个三角形

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


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

	Shader myShader = Shader("vertexSource.glsl", "fragmentSource.glsl");

	glViewport(0, 0, 800, 600);

	stbi_set_flip_vertically_on_load(true);
	// glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	// glCullFace(GL_BACK);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 关闭鼠标显示
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

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
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 创建纹理A
	unsigned int textureBufferA;
	glGenTextures(1, &textureBufferA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureBufferA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 导入纹理贴图
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

	// 导入纹理B
	unsigned int textureBufferB;
	glGenTextures(1, &textureBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureBufferB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("pic.jpg", &width, &height, &nrChannel, 0);
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

	// VAO顶点坐标
	// 第一个参数为VAO槽的位置即上文GLSL中layout的值，第二个参数为一个顶点由几个数构成这里为vec3所以是3个
	// 第三个参数为数据类型这里为float，第四个参数为是否标准化我们已经标准化所以false
	// 第五个参数为步长即下一个顶点数据距离开头现在的数据开头有多远，第六个参数为偏移量顶点数据从头开始，没有偏移量，但颜色数据在顶点数据之后所以有3个float偏移
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 颜色信息
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

	// 纹理信息
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	myShader.use();
	glUniform1i(glGetUniformLocation(myShader.ID, "box"), 0);
	glUniform1i(glGetUniformLocation(myShader.ID, "wife"), 1);


	// 构造变换矩阵
	// glm::mat4 trans = glm::mat4(1.0f);
	// glm::mat4 trans1 = glm::mat4(1.0f);
	// trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	// trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
	//  glm::translate(trans, glm::vec3(0.5, 0, 0));

	// unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
	// glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	// 坐标变换
	glm::mat4 projection = glm::mat4(1.0f);
	// projection transform
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	// view transform
	glm::mat4 view = glm::mat4(1.0f);
	view = camera->getViewMatrix();

	// model transform
	glm::mat4 model = glm::mat4(1.0f);
	// model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 1.0f));

	
	glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));


	while (!glfwWindowShouldClose(window))
	{
		processInput(window, camera);
		// model = glm::rotate(model, glm::radians(0.05f), glm::vec3(0.5f, 1.0f, 0.0f));
		// model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0, 0));

		// trans = glm::rotate(trans, glm::radians(0.01f), glm::vec3(0.0, 0.0, 1.0));
		// trans = glm::scale(trans, glm::vec3(0.9999f, 0.9999f, 0.9999f));

		// unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
		// glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		// 清理颜色缓冲区，并给屏幕glClearColor中的颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
		glm::mat4 model2;
		for (int i = 0; i < 10; i++)
		{
			model2 = glm::mat4(1.0f);
			model2 = glm::translate(model2, cubePositions[i]);
			
			myShader.use();

			view = camera->getViewMatrix();
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model2));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		//glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		//glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		//// 清理颜色缓冲区，并给屏幕glClearColor中的颜色
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureBufferA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureBufferB);*/

		/*glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/

		// glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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


float currentTime = 0.0f, lastTime = 0.0f, deltaTime = 0.0f;
void processInput(GLFWwindow* window, Camera* camera) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	float cameraSpeed = deltaTime * 2.5f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->Position += cameraSpeed * camera->Forward;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->Position -= cameraSpeed * camera->Forward;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->Position -= camera->Right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->Position += camera->Right * cameraSpeed;
}

float lastX, lastY;
bool firstMove = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMove)
	{
		lastX = xpos;
		lastY = ypos;
		firstMove = false;
	}

	float deltaX, deltaY;
	deltaX = xpos - lastX;
	deltaY = - (ypos - lastY);

	lastX = xpos;
	lastY = ypos;

	// std::cout << deltaX << std::endl;

	float sensitivity = deltaTime * 0.2f; // 鼠标灵敏度
	deltaX *= sensitivity;
	deltaY *= sensitivity;

	camera->handleMouseMove(deltaX, deltaY);
}


