#include "Cube.h"

Cube::Cube()
{
	m_Vertices.reserve(8);
	m_Vertices =
	{
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),       // lower left near 0
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),        // lower right near 1
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower left far 2
		Vertex(glm::vec3(0.5f,  -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower right far 3
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.98f, 0.72f, 0.01f), glm::vec3(0.0f), glm::vec2(0.0f)),     // upper left near 4
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.94f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),      // upper right near 5
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.01f, 0.98f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),    // upper left far 6
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.58f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f))      // upper right far 7
	};

	m_Indices.reserve(2 * 3 * 6);
	m_Indices =
	{
		// bottom square
		0, 1, 2,
		2, 1, 3,
		// near square
		0, 4, 5,
		0, 1, 5,
		// left square
		0, 2, 4,
		2, 4, 6,
		// far square
		2, 6, 3,
		3, 6, 7,
		// right square
		1, 3, 7,
		1, 5, 7,
		// top square
		4, 5, 6,
		5, 6, 7
	};
}

Cube::~Cube() {}
