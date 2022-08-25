#version 330 core

in vec2 TexCoord;
in vec4 vertexColor;        						
out vec4 FragColor;

uniform sampler2D box;
uniform sampler2D wife;

void main()					
{							
	// FragColor = vertexColor;
	 FragColor = mix(texture(box, TexCoord), texture(wife, vec2(TexCoord.x, TexCoord.y)),0.5);
	// FragColor = texture(smile, TexCoord);
}							