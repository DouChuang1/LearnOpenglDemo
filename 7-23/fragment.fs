#version 330
//�������Զ�����ɫ�� ��Ҫ������ɫ������ out ����
out vec4 FragColor;
in vec3 ourColor;
in vec3 TexCoord;
uniform sampler2D ourTexture;
void main()
{
	FragColor = texture(ourTexture,TexCoord.xy)*vec4(ourColor,1.0) ; //���
}