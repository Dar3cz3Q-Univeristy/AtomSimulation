#pragma once

#include "Particle.h"

class Electron
{
public:
	Electron(const glm::vec3& position, float scale, float angularSpeed, const glm::vec3& rotationAxis, const glm::vec3& color = glm::vec3(.5f));
	Electron& operator=(const Electron& electron) = delete;
	~Electron();

	void Draw(Shader& shader);
	ParticleType GetType() const { return m_Type; };
	glm::vec3& GetPosition() { return m_Position; };
	glm::vec3& GetColor() { return m_Color; };
private:
	ParticleType m_Type = ELECTRON;
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	glm::vec3 m_RotationAxis;
	float m_Scale;
	float m_AngularSpeed;

	const glm::vec3 c_CenterPoint = glm::vec3(0.0f);
	const glm::vec4 c_Geometry = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 RotateAroundPoint();
};

