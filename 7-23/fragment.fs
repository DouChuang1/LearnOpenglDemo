#version 330
//�������Զ�����ɫ�� ��Ҫ������ɫ������ out ����
out vec4 FragColor;
in vec3 TexCoord;
uniform sampler2D ourTexture;
uniform sampler2D otherTexture;
void main()
{
	FragColor = mix(texture(ourTexture,TexCoord.xy),texture(otherTexture,TexCoord.xy),0.2) ; //���
}