#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
};

struct LightDirectional
{
	vec3 dirTolight;
	vec3 color;
};

struct LightPoint
{
	float Kc;
	float Kl;
	float Kq;
	vec3 position;
	vec3 color;
};

struct LightSpot
{
	float Kc;
	float Kl;
	float Kq;
	vec3 position;
	vec3 color;
	vec3 dirTolight;
	float cosInner;
	float cosOutter;
};


in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 vertexColor;    

out vec4 FragColor;

uniform Material material;
uniform LightSpot sLight;
uniform LightPoint pLight0;
uniform LightPoint pLight1;
uniform LightPoint pLight2;
uniform LightPoint pLight3;
uniform LightDirectional dLight;

// uniform sampler2D box;
uniform sampler2D wife;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform vec3 lightDirUniform;


vec3 CalcDirLight(LightDirectional light, vec3 normal, vec3 dirTocamera)
{
	vec3 result = vec3(0.0f);
	// diffuse
	float diffAmount = max(dot(light.dirTolight, normal), 0);
	vec3 diffuse = diffAmount * light.color * texture(material.diffuse, TexCoord).rgb; 

	// specular
	vec3 r = normalize(reflect(-light.dirTolight, normal));
	float specAmount = pow(max(dot(r, dirTocamera), 0), material.shininess);
	vec3 specular = specAmount * light.color * texture(material.specular, TexCoord).rgb;

	result += diffuse + specular;
	return result;
}

vec3 CalcPoiLight(LightPoint light, vec3 normal, vec3 dirTocamera)
{
	vec3 result = vec3(0.0f);
	// Ë¥¼õÁ¿
	float dist = length(light.position - FragPos);
	float attenuation = 1 / (light.Kc + dist * light.Kl + dist * dist * light.Kq);

	// diffuse
	float diffAmount = max(dot(normalize(light.position - FragPos), normal), 0) * attenuation;
	vec3 diffuse = diffAmount * light.color * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 r = normalize(reflect(normalize(FragPos - light.position), normal));
	float specAmount = pow(max(dot(r, dirTocamera), 0), material.shininess) * attenuation;
	vec3 specular = specAmount * light.color * texture(material.specular, TexCoord).rgb;

	result += diffuse + specular;
	return result;
}

vec3 CalcSpotLight(LightSpot light, vec3 normal, vec3 dirTocamera)
{
	vec3 result = vec3(0.0f);
	// Ë¥¼õÁ¿
	float dist = length(light.position - FragPos);
	float attenuation = 1 / (light.Kc + dist * light.Kl + dist * dist * light.Kq);
	float spotRatio;
	float cosTheta = dot(normalize(-light.dirTolight), normalize(FragPos - light.position));

	if(cosTheta > light.cosInner)
	{
		spotRatio = 1.0f;	
	}
	else if(cosTheta > light.cosOutter)
	{
		spotRatio = (cosTheta - light.cosOutter) / (sLight.cosInner - light.cosOutter);
	}
	else
	{
		spotRatio = 0.0f;
	}
	// diffuse
	float diffAmount = max(dot(normalize(light.position - FragPos), normal), 0);
	vec3 diffuse = diffAmount * light.color * texture(material.diffuse, TexCoord).rgb * spotRatio * attenuation;

	// specular
	vec3 r = normalize(reflect(normalize(FragPos - light.position), normal));
	float specAmount = pow(max(dot(r, dirTocamera), 0), material.shininess);
	vec3 specular = specAmount * light.color * texture(material.specular, TexCoord).rgb * spotRatio * attenuation;

	result += diffuse + specular;
	return result;
}

void main()					
{							
	vec3 finalResult = vec3(0.0f);
	vec3 uNormal = normalize(Normal);
	vec3 dirTocamera = normalize(cameraPos - FragPos);

	vec3 pointLights = vec3(0.0f);
	pointLights = pointLights + CalcPoiLight(pLight0, uNormal, dirTocamera) + CalcPoiLight(pLight1, uNormal, dirTocamera) 
								+ CalcPoiLight(pLight2, uNormal, dirTocamera) + CalcPoiLight(pLight3, uNormal, dirTocamera);

	finalResult += CalcDirLight(dLight, uNormal, dirTocamera);
	finalResult += pointLights;
	finalResult += CalcSpotLight(sLight, uNormal, dirTocamera);
	finalResult += material.ambient * objectColor; 
	FragColor = vec4(finalResult, 1.0f);
}							