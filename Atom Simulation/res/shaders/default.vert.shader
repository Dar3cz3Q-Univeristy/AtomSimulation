#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec4 v_Color;
uniform mat4 u_MVP;
uniform mat4 u_Model;

void main() 
{
	gl_Position = u_MVP * u_Model * vec4(position, 1.0f);
	v_Color = vec4(color, 1.0f);
};