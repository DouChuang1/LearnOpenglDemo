#include "Shader.h"
#include <iostream>
using namespace std;

Shader::Shader(const char *shaderSource, ShaderType st)
{
	//����shader���
	if (st == ShaderType::VERTEX)
	{
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	}
	else if(st == ShaderType::FRAGMENT)
	{
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	}

	//��Դ��
	glShaderSource(shaderId, 1, &shaderSource, NULL);
	//����Դ��
	glCompileShader(shaderId);

	//��ȡ����״̬
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

	//��ȡ������־
	GLint logLen = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLen);

	if (logLen > 0)
	{
		char * log = new char[logLen];
		glGetShaderInfoLog(shaderId, logLen, NULL, log);
		cout << log << endl;
		delete[] log;
	}
}

Shader::~Shader()
{
	if (shaderId != 0)
	{
		glDeleteShader(shaderId);
		shaderId = 0;
	}
}