
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"

using namespace std;

//camera setting
Camera *camera = new Camera(glm::vec3(0.0, 0.0f, 3.0f));

//walk around setting
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0f / 2.0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window= glfwCreateWindow(800,600,"OpenGL",nullptr,nullptr);

	//opengl ����ģʽ���߳� Ҫ����opengl api���ڵ�һ�߳��ڽ���
	//����߳�ͬʱ���ò�������
	//�����window�뵱ǰmain�������߳�
	glfwMakeContextCurrent(window);

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//��������

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,0.0f
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

	unsigned int indices[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};
	VAO *vao1 = new VAO();

	vector<int> layout = { 0,1 };
	vao1->AddVertex3D(vertices, 36, layout);
	//vao1->SetIndexData(indices,6);

	Shader *shader = new Shader("vert.vs", "fragment.fs");

	int width, height, nrChannels;

	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	GLuint texId = 0;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	//�����װ�Լ�����ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);

	GLuint texId2 = 0;
	glGenTextures(1, &texId2);
	glBindTexture(GL_TEXTURE_2D, texId2);
	//�����װ�Լ�����ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//1�ֽڶ���

	shader->use();
	shader->setInt("ourTexture", 0);
	shader->setInt("otherTexture", 1);
	glViewport(0, 0, 800, 600);  //ָ��opengl��Ⱦ����λ�� �Լ���С
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //���ڴ�С�ı� �ص�ִ��framebuffer_size_callback ����ָ����Ⱦ�ӿ�
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//����
	while (!glfwWindowShouldClose(window))   //���ر�һֱ����
	{
		// per-frame time logic
	   // --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//����ָ����ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//����Ԫ 0-31 ���
		//��������Ԫ��0
		//GLuint texLoc = glGetUniformLocation(program->programId, "tex");
		//����0��λ��Ԫ
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texId);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texId2);

		//����任

		//ͶӰ����
		glm::mat4 projection;
		projection = glm::perspective(camera->Zoom, 800.0f / 600.0f, 0.1f, 100.0f);

		shader->use();
		//�����������
		glm::mat4 view;
		view = camera->GetViewMatrix();
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);
		//unsigned int transformLoc = glGetUniformLocation(shader->ID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		//glUniform1i(texLoc, 0);
		vao1->BindVAO();
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		processInput(window); //���������¼� ��Escape �رմ���
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//�ͷ�
	glfwTerminate();
	delete vao1;
	delete shader;
	return 0;
}

