#include "Shader.h"

VAO::VAO()
{
	glGenVertexArrays(1, &vao);
}

int VAO::AddVertex3D(float *data, int vertexCount, std::vector<int> layout)
{
	glBindVertexArray(vao);

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount*3 * sizeof(float)*layout.size(), data, GL_STATIC_DRAW);
	std::cout << layout.size() << std::endl;
	//��layout������
	for (int i = 0;i < layout.size();i++)
	{
		GLvoid* pointer = nullptr;
		if (i == 0)
		{
			pointer = (GLvoid*)0;
		}
		else
		{
			pointer = (GLvoid*)(3 *i* sizeof(float));
		}
		glVertexAttribPointer(layout[i], 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float)*layout.size(), pointer);
		std::cout << layout.size() << std::endl;
		glEnableVertexAttribArray(layout[i]);         //layoutΪ0�ĵ�Ԫ��
	}
	

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
