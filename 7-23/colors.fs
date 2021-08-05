#version 330 core

struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
void main()
{
	vec3 textureCol = texture(material.diffuse,TexCoords).rgb;
	vec3 ambient =light.ambient*textureCol;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position-FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff*light.diffuse*textureCol;

	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = spec*textureCol*light.specular;

	vec3 result = ambient+diffuse+specular;
	FragColor = vec4(result,1.0);
}