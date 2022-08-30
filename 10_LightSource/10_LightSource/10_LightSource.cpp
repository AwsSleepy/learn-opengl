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
// �ڴ��ڴ�С�ı�ʱ���ص��ú����ı䴰�ڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// ���̿��ƻص�����
void processInput(GLFWwindow* window, Camera* camera);
// �����ƻص�����
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

// ʮ�����ӵ�λ��
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
// �����������
// Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); ����position�Լ�target��������췽��
Camera* camera = new Camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region LightDeclare
// LightDirectional* Light = new LightDirectional(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(45.0f, 0, 0)); // ƽ�й����Positionֻ��Ϊ�˷����½����Դ��ʱ��д���룬ƽ�йⲻ��ҪPosition
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
	// ����������ͼ
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
	stbi_set_flip_vertically_on_load(true); 
	glEnable(GL_DEPTH_TEST); // ��Ȼ���
	// �ر������ʾ
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
#pragma endregion

	#pragma region Init and Use Shader
	// ����Shader
	Shader myShader = Shader("vertexSource.glsl", "fragmentSource.glsl");
	myShader.use();
#pragma endregion

	#pragma region Init Material
	Material* myMaterial = new Material(&myShader, glm::vec3(0.2f, 0.2f, 0.2f), LoadImageToGPU("box.png", GL_RGBA, GL_RGBA, 0), LoadImageToGPU("specular.png", GL_RGBA, GL_RGBA, 1), 64);
#pragma endregion

	#pragma region Init and Load Models to VAO, VBO
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

	// VAO��������
	// ��һ������ΪVAO�۵�λ�ü�����GLSL��layout��ֵ���ڶ�������Ϊһ�������ɼ�������������Ϊvec3������3��
	// ����������Ϊ������������Ϊfloat�����ĸ�����Ϊ�Ƿ��׼�������Ѿ���׼������false
	// ���������Ϊ��������һ���������ݾ��뿪ͷ���ڵ����ݿ�ͷ�ж�Զ������������Ϊƫ�����������ݴ�ͷ��ʼ��û��ƫ����������ɫ�����ڶ�������֮��������3��floatƫ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ������Ϣ
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
#pragma endregion

	#pragma region Init and Load Textures
	// ��������A
	//unsigned int textureBufferA;
	//textureBufferA = LoadImageToGPU("box.jpg", GL_RGB, GL_RGB, 0);

	//// ��������B
	//unsigned int textureBufferB;
	//textureBufferB = LoadImageToGPU("pic.jpg", GL_RGB, GL_RGB, 1);
#pragma endregion

	#pragma region Prepare MVP Matrices
	// ����任
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
		// ������ɫ��������������ĻglClearColor�е���ɫ.
		// ������Ȼ�����
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 10; i++)
		{
			// ����model�任����
			model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			// ���ò���
			// 1.����ShaderProgram����ʵĿǰ�����濪һ�߾����ˣ�ʡ����һ��Ч����һ����
			myShader.use();
			// 2.���ò�������,��ʵĿǰ����������һ�߾����ˣ�ʡ������Ч����һ����
			/*glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureBufferA);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textureBufferB);*/

			// 3.����Uniforms
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
			
			
			// ����ģ��
			glBindVertexArray(VAO);

			// ����ͼ��
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Ϊ��һ��ѭ����׼��
		// ������Ӧ
		processInput(window, camera);
		// ѭ���и��ݼ����������view����
		view = camera->getViewMatrix();
		
		// ˫���壬����ǰ�󻺳�
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

	float sensitivity = deltaTime * 0.25f; // ���������
	deltaX *= sensitivity;
	deltaY *= sensitivity;

	camera->handleMouseMove(deltaX, deltaY);
}


