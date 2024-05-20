#version 330 core

layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 aColor;

out vec3 color;
out vec3 v_TexCoord;

uniform mat4 u_VP;

void main() {
	gl_Position = u_VP * vec4(position, 1.0);
	//color = aColor;
	color = vec3(255, 0, 0);
	v_TexCoord = vec3(position.x, position.y, -position.z);
}