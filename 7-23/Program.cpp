#include "Shader.h"
#include <iostream>
using namespace std;

Program::Program(GLint vertexShader,GLint fragmentShader)
{
	programId = glCreateProgram();
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);

	glLinkProgram(programId);
	//获取错误日志
	GLint logLen = 0;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLen);

	if (logLen > 0)
	{
		char * log = new char[logLen];
		glGetProgramInfoLog(programId, logLen, NULL, log);
		cout << log << endl;
		delete[] log;
	}

}

Program::~Program()
{
	if (programId != 0)
	{
		glDeleteProgram(programId);
		programId = 0;
	}
}

int Program::UseProgram()
{
	glUseProgram(programId);
	return 0;
}