#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 texCoords;

out vec4 v_Color;
uniform mat4 u_VP;
uniform mat4 u_Model;
uniform vec4 u_Color;

void main() 
{
	gl_Position = u_VP * u_Model * vec4(position, 1.0f);
	v_Color = u_Color;
};