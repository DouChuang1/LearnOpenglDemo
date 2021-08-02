
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
using namespace std;

#define STRINGIZE(x) #x
#define SHADER(shader) "" STRINGIZE(shader)

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

	float vertex1[] =
	{
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};

	VAO *vao1 = new VAO();

	vector<int> layout = { 0,1 };
	vao1->AddVertex3D(vertex1, 3, layout);

	float aa = 1;
	//shader源码
	const char * vertexShaderSource = SHADER(
		#version 330\n
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aColor;

		out vec3 ourColor;
		void main()
		{
			gl_Position = vec4(aPos, 1.0); //输出
			ourColor = aColor;
		}
	);

	const char * fragmentShaderSource = SHADER(
		#version 330\n
		//输入来自顶点着色器 需要顶点着色器定义 out 变量
		out vec4 FragColor;
		in vec3 ourColor;
		void main()
		{
			FragColor = vec4(ourColor,1.0) ; //输出
		}
	);
	Shader *vertexShader = new Shader(vertexShaderSource, ShaderType::VERTEX);
	Shader *fragmentShader = new Shader(fragmentShaderSource, ShaderType::FRAGMENT);
	
	Program * program = new Program(vertexShader->shaderId, fragmentShader->shaderId);

	int imgWidth = 2;
	int imgHeight = 2;

	unsigned char imgData[]=
	{
		255,0,0,     0,255,0,
		0,0,255,     127,127,127
	};

	//GLuint texId = 0;
	//glGenTextures(1, &texId);

	//glBindTexture(GL_TEXTURE_2D, texId);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//1字节对齐

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);

	glViewport(0, 0, 800, 600);  //指定opengl渲染窗口位置 以及大小
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //窗口大小改变 回调执行framebuffer_size_callback 重新指定渲染视口
	//绘制
	while (!glfwWindowShouldClose(window))   //不关闭一直绘制
	{
		//清屏指定颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		program->UseProgram();

		GLuint loc = glGetUniformLocation(program->programId, "outColor");

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(loc, 0.0f,greenValue,0.0f,1.0f);

		//tex传给shader  使用glUniform1i 
		//纹理单元 0-31 编号
		//传入纹理单元号0
		//GLuint texLoc = glGetUniformLocation(program->programId, "tex");
		//激活0号位单元
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texId);
		//glUniform1i(texLoc, 0);

		//vao->Draw();
		//aa += 0.003;
		vao1->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window); //监听输入事件 按Escape 关闭窗口
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//释放
	glfwTerminate();
	delete vao1;
	delete vertexShader;
	delete fragmentShader;
	delete program;
	return 0;
}

