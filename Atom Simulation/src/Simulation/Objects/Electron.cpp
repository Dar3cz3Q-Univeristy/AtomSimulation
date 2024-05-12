#include "Electron.h"

Electron::Electron(const glm::vec3& position, unsigned int count, float rotationAngle, const glm::vec3& rotationAxis, const glm::vec3& color)
	: m_Position(position), m_Color(color), m_RotationAxis(rotationAxis), m_RotationAngle(rotationAngle), m_Count(count)
{
}

Electron::~Electron() {}

void Electron::Draw(Shader& shader)
{
	shader.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

	// Rotating around center of 0, 0, 0 point
	glm::vec3 point(0, 0, 0);
	glm::vec4 geom(0, 0, 0, 1);

	glm::mat4 t1 = glm::translate(glm::mat4(1), -point);
	glm::mat4 r = glm::rotate(glm::mat4(1), glm::radians(m_RotationAngle), m_RotationAxis);
	glm::mat4 t2 = glm::translate(glm::mat4(1), point);

	glm::mat4 temp = t2 * r * t1;

	m_Position = temp * glm::translate(glm::mat4(1), m_Position) * geom;

	shader.SetUniformMat4f("u_Model", model);

	shader.SetUniform4f("u_Color", m_Color.r, m_Color.g, m_Color.b, 1.0f);

	GLCall(glDrawElements(GL_TRIANGLES, m_Count, GL_UNSIGNED_INT, nullptr));
}
