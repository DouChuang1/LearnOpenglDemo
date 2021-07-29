#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

enum ShaderType
{
	VERTEX = 1,
	FRAGMENT = 2
};

class Shader
{
public:
	Shader(const char *shaderSource, ShaderType st);
	~Shader();
	GLint shaderId;
	
};


class Program
{
public:
	Program(GLint vertexShader, GLint fragmentShader);
	~Program();

	int UseProgram();
public:
	GLint programId = 0;
};


class VAO
{
public:
	VAO();
	~VAO();

	int AddVertex3D(float *data, int vertexCount, int layout);

	int BindVAO();

	int SetIndexData(unsigned int *indexData, int indexCount);

	int Draw();

private:
	GLuint vao=0;
	GLuint ebo = 0;
	int drawTime = 0;
	std::vector<GLuint> vboList;
};