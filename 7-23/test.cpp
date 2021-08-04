
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

//light setting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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

	//opengl 运行模式单线程 要调用opengl api是在单一线程内进行
	//多个线程同时调用不被允许
	//绑定这个window与当前main函数的线程
	glfwMakeContextCurrent(window);

	//初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	//顶点数据

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	VAO *vao1 = new VAO();
	vector<int> layout = { 0,1 };
	vao1->AddVertex3D(vertices, 36, layout);
	VAO *vao2 = new VAO();
	vao2->AddVertex3D(vertices, 36, layout);

	Shader *lightShader = new Shader("light.vs", "light.fs");

	Shader *colorsShader = new Shader("colors.vs", "colors.fs");

	glEnable(GL_DEPTH_TEST);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //窗口大小改变 回调执行framebuffer_size_callback 重新指定渲染视口
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	// tell GLFW to capture our mouse
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//绘制
	while (!glfwWindowShouldClose(window))   //不关闭一直绘制
	{
		// per-frame time logic
	   // --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//清屏指定颜色
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		colorsShader->use();
		colorsShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		//构建相机矩阵
		glm::mat4 view;
		view = camera->GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)800 / (float)600, 0.1f, 100.0f);
		colorsShader->setMat4("view", view);
		colorsShader->setMat4("projection", projection);
		lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		colorsShader->setVec3("lightPos", lightPos);
		colorsShader->setVec3("viewPos", camera->Position);
		colorsShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		colorsShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		colorsShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		colorsShader->setFloat("material.shininess", 32);
		
		glm::mat4 model = glm::mat4(1.0f);
		colorsShader->setMat4("model", model);
		vao1->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader->use();
		lightShader->setMat4("projection", projection);
		lightShader->setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lightShader->setMat4("model", model);

		vao2->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 36);
		processInput(window); //监听输入事件 按Escape 关闭窗口
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//释放
	glfwTerminate();
	delete vao1;
	delete colorsShader;
	delete lightShader;
	return 0;
}

