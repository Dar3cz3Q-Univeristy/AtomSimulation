#pragma once

#include "Particle.h"

class Electron
{
public:
	Electron(const glm::vec3& position, unsigned int count, float rotationAngle, const glm::vec3& rotationAxis, const glm::vec3& color = glm::vec3(1.0f));
	~Electron();

	void Draw(Shader& shader);
	const ParticleType GetType() const { return m_Type; };
	glm::vec3& GetPosition() { return m_Position; };
	glm::vec3& GetColor() { return m_Color; };
private:
	const ParticleType m_Type = ELECTRON;
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	glm::vec3 m_RotationAxis;
	float m_RotationAngle;
	unsigned int m_Count;
};

