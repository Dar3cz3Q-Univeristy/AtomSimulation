#include "Electron.h"
#include "Window.h"

Electron::Electron(const glm::vec3& position, float scale, float angularSpeed, const glm::vec3& rotationAxis, const glm::vec3& color)
	: m_Position(position), m_Color(color), m_RotationAxis(rotationAxis), m_Scale(scale), m_AngularSpeed(angularSpeed) {}

Electron::~Electron() {}

void Electron::Draw(Shader& shader)
{
	shader.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::scale(model, glm::vec3(m_Scale));

	glm::mat4 temp = RotateAroundPoint();

	m_Position = temp * glm::translate(glm::mat4(1), m_Position) * c_Geometry;

	shader.SetUniformMat4f("u_Model", model);

	shader.SetUniform4f("u_Color", m_Color.r, m_Color.g, m_Color.b, 1.0f);

	GLCall(glDrawElements(GL_TRIANGLES, SPHERE_INDICIES_COUNT, GL_UNSIGNED_INT, nullptr));
}

glm::mat4 Electron::RotateAroundPoint()
{
	auto t1 = glm::translate(glm::mat4(1), -c_CenterPoint);
	auto r = glm::rotate(glm::mat4(1), glm::radians(m_AngularSpeed) * Window::GetDeltaTime(), m_RotationAxis);
	auto t2 = glm::translate(glm::mat4(1), c_CenterPoint);

	return t2 * r * t1;
}