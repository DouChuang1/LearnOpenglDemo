
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
using namespace std;

#define STRINGIZE(x) #x
#define SHADER(shader) "" STRINGIZE(shader)

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

	float vertex[] =
	{
		-1.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,
	
		1.0f,-1.0f,0.0f,
		-1.0f,-1.0f,0.0f
	};

	unsigned int index[] = {
		0,3,1,
		1,3,2
	};


	float vertexUV[]=
	{
		0.0f,1.0f,0.0f,
		1.0f,1.0f,0.0f,

		1.0f,0.0f,0.0f,
		0.0f,0.0f,0.0f
	};

	VAO *vao = new VAO();
	vao->AddVertex3D(vertex, 6, 0);
	vao->AddVertex3D(vertexUV, 4, 1);
	vao->SetIndexData(index, 6);

	
	float aa = 1;
	//shader源码
	const char * vertexShaderSource = SHADER(
		#version 330\n
		layout(location = 0) in vec3 pos; //输入
		layout(location = 1) in vec3 uvPos; //输入
		out vec3 outPos;
		out vec3 outUVPos;
		uniform float a;
		void main()
		{
			outPos = pos;
			outUVPos = uvPos;
			float _a = sin(a);
			gl_Position = vec4(pos*_a, 1.0); //输出
		}
	);

	const char * fragmentShaderSource = SHADER(
		#version 330\n
		//输入来自顶点着色器 需要顶点着色器定义 out 变量
		out vec4 outColor;
		in vec3 outPos;
		in vec3 outUVPos;
		uniform sampler2D tex;
		void main()
		{
			vec2 uv = vec2(outUVPos.x, outUVPos.y);
			vec4 color = texture(tex, uv);
			outColor = color; //输出
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

	GLuint texId = 0;
	glGenTextures(1, &texId);

	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//1字节对齐

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);

	glViewport(0, 0, 800, 600);
	//绘制
	while (!glfwWindowShouldClose(window))   //不关闭一直绘制
	{
		//
		glClear(GL_COLOR_BUFFER_BIT);
		program->UseProgram();

		GLuint loc = glGetUniformLocation(program->programId, "a");
		glUniform1f(loc, aa);

		//tex传给shader  使用glUniform1i 
		//纹理单元 0-31 编号
		//传入纹理单元号0
		GLuint texLoc = glGetUniformLocation(program->programId, "tex");
		//激活0号位单元
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texId);
		glUniform1i(texLoc, 0);

		vao->Draw();
		aa += 0.003;
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//释放
	glfwTerminate();
	delete vao;
	delete vertexShader;
	delete fragmentShader;
	delete program;
	return 0;
}