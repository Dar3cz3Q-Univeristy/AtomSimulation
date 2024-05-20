#include "DisplayCube.h"

DisplayCube::DisplayCube() 
{
	m_Position = glm::vec3(0.0f, 2.0f, 0.0f);
	m_Scale = 1.0f;
}

DisplayCube::~DisplayCube() {}

void DisplayCube::Draw(Shader& shader)
{
	shader.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::scale(model, glm::vec3(m_Scale));
	shader.SetUniformMat4f("u_Model", model);

	GLCall(glDrawElements(GL_TRIANGLES, CUBE_INDICIES_COUNT, GL_UNSIGNED_INT, nullptr));
}
