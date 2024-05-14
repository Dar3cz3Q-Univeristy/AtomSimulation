#pragma once

#include "Particle.h"

class Electron
{
public:
	Electron(const glm::vec3& position, float scale, float angularSpeed, const glm::vec3& rotationAxis, unsigned int count, const glm::vec3& color = glm::vec3(1.0f));
	~Electron();

	void Draw(Shader& shader);
	const ParticleType GetType() const { return c_Type; };
	glm::vec3& GetPosition() { return m_Position; };
	glm::vec3& GetColor() { return m_Color; };
private:
	const ParticleType c_Type = ELECTRON;
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	glm::vec3 m_RotationAxis;
	float m_Scale;
	float m_AngularSpeed;
	unsigned int m_Count;

	const glm::vec3 c_CenterPoint = glm::vec3(0.0f);
	const glm::vec4 c_Geometry = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 RotateAroundPoint();
};

