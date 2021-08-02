#version 330
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aTexCoord;

out vec3 ourColor;
out vec3 TexCoord;

uniform mat4 transform;
void main()
{
	gl_Position = transform*vec4(aPos, 1.0); //Êä³ö
	ourColor = aColor;
	TexCoord = aTexCoord;
}