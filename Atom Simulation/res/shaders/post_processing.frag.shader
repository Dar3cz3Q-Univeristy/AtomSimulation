#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_ScreenTexture;

void main() 
{
	color = texture(u_ScreenTexture, v_TexCoords);
}