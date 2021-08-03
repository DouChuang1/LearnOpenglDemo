#version 330
//输入来自顶点着色器 需要顶点着色器定义 out 变量
out vec4 FragColor;
in vec3 TexCoord;
uniform sampler2D ourTexture;
uniform sampler2D otherTexture;
void main()
{
	FragColor = mix(texture(ourTexture,TexCoord.xy),texture(otherTexture,TexCoord.xy),0.2) ; //输出
}