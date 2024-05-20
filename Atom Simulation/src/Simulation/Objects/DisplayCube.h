#pragma once

#include "Renderer.h"

class DisplayCube
{
public:
	DisplayCube();
	~DisplayCube();

	void Draw(Shader& shader);
private:
	glm::vec3 m_Position;
	float m_Scale;
};

