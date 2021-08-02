#version 330
//输入来自顶点着色器 需要顶点着色器定义 out 变量
out vec4 FragColor;
in vec3 ourColor;
in vec3 TexCoord;
uniform sampler2D ourTexture;
void main()
{
	FragColor = texture(ourTexture,TexCoord.xy)*vec4(ourColor,1.0) ; //输出
}