
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
	//shaderԴ��
	const char * vertexShaderSource = SHADER(
		#version 330\n
		layout(location = 0) in vec3 aPos;
		layout(location = 1) in vec3 aColor;

		out vec3 ourColor;
		void main()
		{
			gl_Position = vec4(aPos, 1.0); //���
			ourColor = aColor;
		}
	);

	const char * fragmentShaderSource = SHADER(
		#version 330\n
		//�������Զ�����ɫ�� ��Ҫ������ɫ������ out ����
		out vec4 FragColor;
		in vec3 ourColor;
		void main()
		{
			FragColor = vec4(ourColor,1.0) ; //���
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

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//1�ֽڶ���

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);

	glViewport(0, 0, 800, 600);  //ָ��opengl��Ⱦ����λ�� �Լ���С
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //���ڴ�С�ı� �ص�ִ��framebuffer_size_callback ����ָ����Ⱦ�ӿ�
	//����
	while (!glfwWindowShouldClose(window))   //���ر�һֱ����
	{
		//����ָ����ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		program->UseProgram();

		GLuint loc = glGetUniformLocation(program->programId, "outColor");

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(loc, 0.0f,greenValue,0.0f,1.0f);

		//tex����shader  ʹ��glUniform1i 
		//����Ԫ 0-31 ���
		//��������Ԫ��0
		//GLuint texLoc = glGetUniformLocation(program->programId, "tex");
		//����0��λ��Ԫ
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texId);
		//glUniform1i(texLoc, 0);

		//vao->Draw();
		//aa += 0.003;
		vao1->BindVAO();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		processInput(window); //���������¼� ��Escape �رմ���
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//�ͷ�
	glfwTerminate();
	delete vao1;
	delete vertexShader;
	delete fragmentShader;
	delete program;
	return 0;
}

