#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 vertexColor;    

out vec4 FragColor;

uniform Material material;
// uniform sampler2D box;
// uniform sampler2D wife;
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
	vec3 ambient = material.ambient * lightColor * texture(material.diffuse, TexCoord).rgb * lightColor;

	// 满反射
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(0, dot(lightDir, Normal)) * lightColor;
	// vec3 diffuse = texture(material.diffuse, TexCoord).rgb;

	// 镜面反射
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	float specularAmount = pow(max(0, dot(reflectVec, cameraVec)), material.shininess);
	vec3 specular = specularAmount * lightColor * texture(material.specular, TexCoord).rgb;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0f);
}							