#version 330 core

layout (location = 0) out vec4 color;
layout (location = 1) out vec4 bloomColor;

in vec2 v_TexCoords;

uniform float u_Gamma;
uniform sampler2D u_ScreenTexture;
uniform vec2 u_ScreenDimension;

float offset_x = 1.0f / u_ScreenDimension.x;
float offset_y = 1.0f / u_ScreenDimension.y;

const float exposure = 1.0f;

// Functions
vec4 reverseColors(vec4 color);
vec4 gammaCorrection(vec4 color);
vec4 detectEdges(); 
vec4 hdr(vec4 color);

void main() 
{
	vec4 fragmentColor = vec4(texture2D(u_ScreenTexture, v_TexCoords));
	vec4 reverseColor = reverseColors(fragmentColor);
	
	color = hdr(fragmentColor);
	//color = detectEdges();
	//color = reverseColors(fragmentColor);
}

vec4 reverseColors(vec4 color) 
{
	return vec4(1) - color;
};

vec4 gammaCorrection(vec4 color) 
{
	return vec4(pow(color.rgb, vec3(1.0f / u_Gamma)), 1.0f);
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

vec4 detectEdges() 
{
	vec3 temp = vec3(0.0f);
	for(int i = 0; i < 9; i++)
		temp += vec3(texture2D(u_ScreenTexture, v_TexCoords + offsets[i])) * edgeDetectionkernel[i];
	return vec4(temp, 1.0f);
};

vec4 hdr(vec4 color) {
	vec3 toneMapped = vec3(1.0f) - exp(-color.rgb * exposure);
	return gammaCorrection(vec4(toneMapped, 1.0f));
};