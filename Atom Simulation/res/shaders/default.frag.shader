#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;
in vec2 v_TexCoord;
in vec3 v_Normals;

const int MAX_ELECTRON_COUNT = 100;	// Keep number of electrons up to date in Specification.h

uniform int u_ElectronCount;
uniform vec3 u_MultipleLightPos[MAX_ELECTRON_COUNT];
uniform vec3 u_MultipleLightColor[MAX_ELECTRON_COUNT];

void main() 
{
	color = v_Color;
};