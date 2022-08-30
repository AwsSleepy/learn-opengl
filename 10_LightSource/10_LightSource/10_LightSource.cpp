#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#include "stb_image.h"

#pragma region Input Declare
// 在窗口大小改变时，回调该函数改变窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 键盘控制回调函数
void processInput(GLFWwindow* window, Camera* camera);
// 鼠标控制回调函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
#pragma endregion

#pragma region Model Data

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
											 
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
											 
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
											 
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
											 
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
											 
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

// 十个箱子的位置
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
	glm::vec3(-1.3f,  1.0f, -1.5f),
};
#pragma endregion

#pragma region Camera Declare
// 定义摄像机类
// Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); 运用position以及target的相机构造方法
Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region LightDeclare
// LightDirectional* Light = new LightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(45.0f, 0, 0)); // 平行光加上Position只是为了方便新建点光源类时少写代码，平行光不需要Position
// LightPoint* Light = new LightPoint(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(45.0f, 0, 0), glm::vec3(2.0f, 2.0f, 2.0f));
LightSpot* Light = new LightSpot(glm::vec3(0, 5.0f, -2.0f), glm::vec3(90.0f, 0, 0), glm::vec3(2.0f, 2.0f, 2.0f));
#pragma endregion

unsigned int LoadImageToGPU(const char* filename, GLint internalFormat, GLenum format, GLint texttureSlot)
{
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + texttureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 导入纹理贴图
	int width, height, nrChannel;
	unsigned char* data1 = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "load image failed" << std::endl;
	}
	stbi_image_free(data1);
	data1 = nullptr;

	return TexBuffer;
}

int main()
{
	#pragma region Open a Window with glfw and Init glew
	// 初始化glfw
	glfwInit();
	// 告诉glfw我们需要什么版本，什么模式的opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	stbi_set_flip_vertically_on_load(true); 
	glEnable(GL_DEPTH_TEST); // 深度缓冲
	// 关闭鼠标显示
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
#pragma endregion

	#pragma region Init and Use Shader
	// 构造Shader
	Shader myShader = Shader("vertexSource.glsl", "fragmentSource.glsl");
	myShader.use();
#pragma endregion

	#pragma region Init Material
	Material* myMaterial = new Material(&myShader, glm::vec3(0.2f, 0.2f, 0.2f), LoadImageToGPU("box.png", GL_RGBA, GL_RGBA, 0), LoadImageToGPU("specular.png", GL_RGBA, GL_RGBA, 1), 64);
#pragma endregion

	#pragma region Init and Load Models to VAO, VBO
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

	// VAO顶点坐标
	// 第一个参数为VAO槽的位置即上文GLSL中layout的值，第二个参数为一个顶点由几个数构成这里为vec3所以是3个
	// 第三个参数为数据类型这里为float，第四个参数为是否标准化我们已经标准化所以false
	// 第五个参数为步长即下一个顶点数据距离开头现在的数据开头有多远，第六个参数为偏移量顶点数据从头开始，没有偏移量，但颜色数据在顶点数据之后所以有3个float偏移
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 纹理信息
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
#pragma endregion

	#pragma region Init and Load Textures
	// 创建纹理A
	//unsigned int textureBufferA;
	//textureBufferA = LoadImageToGPU("box.jpg", GL_RGB, GL_RGB, 0);

	//// 导入纹理B
	//unsigned int textureBufferB;
	//textureBufferB = LoadImageToGPU("pic.jpg", GL_RGB, GL_RGB, 1);
#pragma endregion

	#pragma region Prepare MVP Matrices
	// 坐标变换
	glm::mat4 projection = glm::mat4(1.0f);
	// projection transform
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	// view transform
	glm::mat4 view = glm::mat4(1.0f);
	// model transform
	glm::mat4 model = glm::mat4(1.0f);
#pragma endregion

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// 清理颜色缓冲区，并给屏幕glClearColor中的颜色.
		// 清理深度缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 10; i++)
		{
			// 设置model变换矩阵
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			// 设置材质
			// 1.开启ShaderProgram，其实目前在外面开一边就行了，省略这一行效果是一样的
			myShader.use();
			// 2.设置材质纹理,其实目前在外面设置一边就行了，省略这里效果是一样的
			/*glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureBufferA);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureBufferB);*/

			// 3.设置Uniforms
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(myShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			/*glUniform1i(glGetUniformLocation(myShader.ID, "box"), 0);
			glUniform1i(glGetUniformLocation(myShader.ID, "wife"), 1);*/
			glUniform3f(glGetUniformLocation(myShader.ID, "objectColor"), 0.6f, 0.6f, 0.6f);
			glUniform3f(glGetUniformLocation(myShader.ID, "cameraPos"), camera->Position.x, camera->Position.y, camera->Position.z);
			glUniform3f(glGetUniformLocation(myShader.ID, "lightPos"), Light->position.x, Light->position.y, Light->position.z); //sin((float)glfwGetTime()) * 
			glUniform3f(glGetUniformLocation(myShader.ID, "lightColor"), Light->color.x, Light->color.y, Light->color.z);
			glUniform3f(glGetUniformLocation(myShader.ID, "lightDirUniform"), Light->direction.x, Light->direction.y, Light->direction.z);
			glUniform1f(glGetUniformLocation(myShader.ID, "lightPoint.Kc"), Light->Kc);
			glUniform1f(glGetUniformLocation(myShader.ID, "lightPoint.Kl"), Light->Kl);
			glUniform1f(glGetUniformLocation(myShader.ID, "lightPoint.Kq"), Light->Kq);
			glUniform1f(glGetUniformLocation(myShader.ID, "lightSpot.cosInner"), Light->cosInnerPhy);
			glUniform1f(glGetUniformLocation(myShader.ID, "lightSpot.cosOutter"), Light->cosOutterPhy);

			myShader.setUniform3f("material.ambient", myMaterial->ambient);
			myShader.setUniform1i("material.diffuse", 0);
			myShader.setUniform1i("material.specular", 1);
			myShader.setUniform1i("material.shininess", myMaterial->shininess);
			
			
			// 设置模型
			glBindVertexArray(VAO);

			// 画出图像
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// 为下一次循环做准备
		// 键盘响应
		processInput(window, camera);
		// 循环中根据键盘输入更新view矩阵
		view = camera->getViewMatrix();
		
		// 双缓冲，交换前后缓冲
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

	float cameraSpeed = deltaTime * 2.7f;
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

	float sensitivity = deltaTime * 0.25f; // 鼠标灵敏度
	deltaX *= sensitivity;
	deltaY *= sensitivity;

	camera->handleMouseMove(deltaX, deltaY);
}


