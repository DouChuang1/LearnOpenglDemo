#include "Shader.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
}

int VAO::AddVertex3D(float *data, int vertexCount, int layout)
{
	glBindVertexArray(vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount*3 * sizeof(float), data, GL_STATIC_DRAW);

	//往layout传参数
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(layout);         //layout为0的单元打开

	vboList.push_back(vbo);
	glBindVertexArray(0);

	return 0;
}

VAO::~VAO()
{
	for (int i = 0;i < vboList.size();i++)
	{
		GLuint vbo = vboList[i];
		glDeleteBuffers(1, &vbo);
	}

	vboList.clear();

	if (ebo != NULL)
	{
		glDeleteVertexArrays(1, &ebo);
		ebo = NULL;
	}

	if (vao != NULL)
	{
		glDeleteVertexArrays(1, &vao);
		vao = NULL;
	}
}

int VAO::BindVAO()
{
	glBindVertexArray(vao);
	return 0;
}

int VAO::SetIndexData(unsigned int *indexData, int indexCount)
{
	glBindVertexArray(vao);

	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount*sizeof(unsigned int), indexData, GL_STATIC_DRAW);

	drawTime = indexCount;
	glBindVertexArray(0);
	return 0;
}

int VAO::Draw()
{
	BindVAO();
	glDrawElements(GL_TRIANGLES, drawTime, GL_UNSIGNED_INT, 0);

	return 0;
}
