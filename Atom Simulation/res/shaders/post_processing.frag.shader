#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform float u_Gamma;
uniform sampler2D u_ScreenTexture;

vec4 reverseColors(vec4 color) 
{
	return vec4(1) - color;
}

vec3 gammaCorrection(vec4 color) 
{
	return pow(color.rgb, vec3(1.0f / u_Gamma));
}

void main() 
{
	vec4 fragmentColor = vec4(texture2D(u_ScreenTexture, v_TexCoords));
	vec4 reverseColor = reverseColors(fragmentColor);

	color.rgb = gammaCorrection(fragmentColor);
}