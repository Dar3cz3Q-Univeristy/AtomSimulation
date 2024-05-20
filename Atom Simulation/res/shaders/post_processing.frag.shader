#version 330 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform float u_Gamma;
uniform sampler2D u_ScreenTexture;

const float offset_x = 1.0f / 800.0f;
const float offset_y = 1.0f / 800.0f;

vec4 reverseColors(vec4 color) 
{
	return vec4(1) - color;
};

vec3 gammaCorrection(vec4 color) 
{
	return pow(color.rgb, vec3(1.0f / u_Gamma));
};

vec2 offsets[9] = vec2[]
(
	vec2(-offset_x, offset_y),   vec2(0.0f, offset_y),    vec2(offset_x, offset_y),
	vec2(-offset_x, 0.0f),       vec2(0.0f, 0.0f),	      vec2(offset_x, 0.0f),
	vec2(-offset_x, -offset_y),  vec2(0.0f, -offset_y),   vec2(offset_x, -offset_y)
);

float edgeDetectionkernel[9] = float[]
(
	1,  1, 1,
	1, -8, 1,
	1,  1, 1
);

vec3 detectEdges() 
{
	vec3 temp = vec3(0.0f);
	for(int i = 0; i < 9; i++)
		temp += vec3(texture2D(u_ScreenTexture, v_TexCoords + offsets[i])) * edgeDetectionkernel[i];
	return temp;
};

void main() 
{
	vec4 fragmentColor = vec4(texture2D(u_ScreenTexture, v_TexCoords));
	vec4 reverseColor = reverseColors(fragmentColor);

	color.rgb = gammaCorrection(fragmentColor);
	//color = vec4(detectEdges(), 1.0f);
}