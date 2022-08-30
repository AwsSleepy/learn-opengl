#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int shininess;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 vertexColor;    

out vec4 FragColor;

uniform Material material;
uniform sampler2D box;
uniform sampler2D wife;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()					
{							
	// FragColor = vertexColor;
	// FragColor = texture(wife, TexCoord);
	// FragColor = texture(smile, TexCoord);

	// 环境光
	float ambientStrength = 0.2f;
	vec3 ambient = material.ambient * lightColor;

	// 满反射
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = max(0, dot(lightDir, Normal)) * lightColor * material.diffuse;


	// 镜面反射
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	float specularAmount = pow(max(0, dot(reflectVec, cameraVec)), material.shininess);
	vec3 specular = specularAmount * lightColor * material.specular;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0f) * texture(wife, TexCoord);
}							