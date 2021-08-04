#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

out vec4 FragColor;

uniform vec3 lightColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;

uniform vec3 viewPos;
void main()
{
	float ambientStrength = 1;
	vec3 ambient = ambientStrength*light.ambient*material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff*light.diffuse*material.diffuse;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos-FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = specularStrength*spec*material.specular*light.specular;

	vec3 result = ambient+diffuse+specular;
	FragColor = vec4(result,1.0);
}