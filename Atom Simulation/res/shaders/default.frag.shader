#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normals;

uniform vec3 u_MultipleLightPos[3];
uniform vec3 u_MultipleLightColor[3];

void main() 
{
	color = v_Color;
};