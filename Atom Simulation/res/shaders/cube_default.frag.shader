#version 330 core

in vec3 color;
in vec3 v_TexCoord;

out vec4 FragColor;

uniform samplerCube u_Texture;

void main()
{
	FragColor = vec4(color, 1.0f);
	//FragColor = texture(u_Texture, v_TexCoord);
}