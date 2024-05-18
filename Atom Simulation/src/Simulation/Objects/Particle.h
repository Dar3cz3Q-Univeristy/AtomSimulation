#pragma once

#include "Renderer.h"
#include "Specification.h"

#include "glm/gtc/matrix_transform.hpp"

enum ParticleType {
	PROTON, NEUTRON, ELECTRON
};

class Particle
{
public:
	Particle(ParticleType type, const glm::vec3& position, float scale);
	~Particle();

	void Draw(Shader& shader);
	ParticleType GetType() const { return m_Type; };
private:
	ParticleType m_Type;
	glm::vec3 m_Position;
	glm::vec3 m_Color;
	float m_Scale;
};

