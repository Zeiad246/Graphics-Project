#version 330 core

#define LIGHTS_COUNT 2

struct DirectionalLight {
	vec4 ambient, diffuse, specular, direction;
};

struct PointLight {
	float constant, linear, quadratic;
    vec4 ambient, diffuse, specular, position;
};

struct Material {
	float shininess;
	vec4 ambient, diffuse, specular;
};

in vec3 normal, position;

uniform vec3 camera;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[LIGHTS_COUNT];
uniform Material material;

out vec4 color;

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec4 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 norm = normalize(normal);
	vec3 viewDir = normalize(camera - position);

	vec4 result = CalculateDirectionalLight(directionalLight, norm, viewDir);

	for(int i = 0; i < LIGHTS_COUNT; i++) {
		result += CalculatePointLight(pointLights[i], norm, position, viewDir);
	}

	color = result;
	
	color.a = 1.0;
}

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec4 ambient = light.ambient * material.ambient;
	
	vec3 lightDir = normalize(- light.direction.xyz);
	
	float Kd = max(dot(normal, lightDir), 0.0);
	vec4 diffuse = Kd * light.diffuse * material.diffuse;

	vec3 reflectDir = reflect(-lightDir, normal);
	float Ks = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec4 specular = Ks * light.specular * material.specular;

	return ambient + diffuse + specular;
}

vec4 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);

    float Kd = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float Ks = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    vec4 ambient = light.ambient * material.ambient;
    vec4 diffuse = Kd * light.diffuse * material.diffuse;
    vec4 specular = Ks * light.specular * material.specular;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}