#version 330 core

layout (location = 0) in vec3 position;

out vec3 v_TexCoord;

uniform mat4 u_VP;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_VP * u_Model * vec4(position, 1.0f);
	v_TexCoord = vec3(position.x, position.y, -position.z);
}
