#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
};

struct LightPoint
{
	float Kc;
	float Kl;
	float Kq;
};

struct LightSpot
{
	float cosInner;
	float cosOutter;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 vertexColor;    

out vec4 FragColor;

uniform Material material;
uniform LightPoint lightPoint;
uniform LightSpot lightSpot;
// uniform sampler2D box;
// uniform sampler2D wife;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform vec3 lightDirUniform;

void main()					
{							
	// FragColor = vertexColor;
	// FragColor = texture(wife, TexCoord);
	// FragColor = texture(smile, TexCoord);
	float dist = length(lightPos - FragPos);
	float attenuation = 1.0f / (lightPoint.Kc + lightPoint.Kl * dist + lightPoint.Kq * dist * dist);

	// 环境光
	vec3 ambient = material.ambient * texture(material.diffuse, TexCoord).rgb;

	// 满反射
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb * max(0, dot(lightDir, Normal)) * lightColor;
	// vec3 diffuse = texture(material.diffuse, TexCoord).rgb;

	// 镜面反射
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	float specularAmount = pow(max(0, dot(reflectVec, cameraVec)), material.shininess);
	vec3 specular = specularAmount * lightColor * texture(material.specular, TexCoord).rgb;

	float cosTheta = dot(normalize(FragPos - lightPos), -lightDirUniform);

	vec3 result;
	// if(cosTheta > lightSpot.cosInner)
	// {
	// 	// inside
	// 	result = (ambient + (diffuse + specular)) ;
	// }
	// else
	// {
	// 	// outside
	// 	result = ambient;
	// }
	float t = (cosTheta - lightSpot.cosOutter) / (lightSpot.cosInner - lightSpot.cosOutter);
	if(cosTheta > lightSpot.cosInner)
	{
		// inside
		result = (ambient + (diffuse + specular)) ;
	}
	else if(cosTheta > lightSpot.cosOutter)
	{
		// middle
		result = (ambient + (diffuse + specular) * t) ;
	}
	else
	{
		// outside
		result = ambient;
	}

	FragColor = vec4(result, 1.0f);
}							