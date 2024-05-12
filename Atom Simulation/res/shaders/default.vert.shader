#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCoords;

out vec4 v_Color;
out vec3 v_Position;
out vec3 v_Normals;
out vec2 v_TexCoord;

uniform mat4 u_VP;
uniform mat4 u_Model;
uniform vec4 u_Color;

void main() 
{
	gl_Position = u_VP * u_Model * vec4(position, 1.0f);

	v_Color = u_Color;
	v_Position = position;
	v_Normals = normals;
	v_TexCoord = texCoords;
};