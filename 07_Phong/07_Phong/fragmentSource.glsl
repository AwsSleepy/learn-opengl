#version 330 core

// in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 vertexColor;    

out vec4 FragColor;

uniform sampler2D box;
uniform sampler2D wife;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()					
{							
	// FragColor = vertexColor;
	// FragColor = mix(texture(box, TexCoord), texture(wife, vec2(TexCoord.x, TexCoord.y)),0.5);
	// FragColor = texture(smile, TexCoord);

	// 环境光
	float ambientStrength = 0.2f;
	vec3 ambient = ambientStrength * ambientColor;

	// 满反射
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 diffuse = max(0, dot(lightDir, Normal)) * lightColor;


	// 镜面反射
	vec3 reflectVec = reflect(-lightDir, Normal);
	vec3 cameraVec = normalize(cameraPos - FragPos);
	float specularAmount = pow(max(0, dot(reflectVec, cameraVec)), 100);
	vec3 specular = specularAmount * lightColor;

	FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0f);
}							