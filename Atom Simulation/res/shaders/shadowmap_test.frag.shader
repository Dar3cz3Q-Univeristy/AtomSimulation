#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main() 
{
	float depthValue = texture(u_Texture, v_TexCoords).r;
    color = vec4(vec3(depthValue * 10.0), 1.0);
}
