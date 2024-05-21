#include "Cube.h"

Cube::Cube()
{
	m_Vertices.reserve(4 * 4);
	m_Vertices =
	{
		//             Positions             //    Normals     //     Colors     //           UV           //
		
		// Front square
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 0.0f)),     // lower left 0    #0
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 0.0f)),     // lower right 1   #1
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 1.0f)),     // upper left 4    #2
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 1.0f)),     // upper right 5   #3

		// Right square
		Vertex(glm::vec3(0.5f, -0.5f, 0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 0.0f)),     // lower left 1    #4
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 0.0f)),     // lower right 3   #5
		Vertex(glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 1.0f)),     // upper left 5    #6
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 1.0f)),     // upper right 7   #7

		// Back square
		Vertex(glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 0.0f)),     // lower left 3    #8
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 0.0f)),     // lower right 2   #9
		Vertex(glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 1.0f)),     // upper left 7    #10
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 1.0f)),     // upper right 6   #11

		// Left square
		Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 0.0f)),     // lower left 2    #12
		Vertex(glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 0.0f)),     // lower right 0   #13
		Vertex(glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(0.0f, 1.0f)),     // upper left 6    #14
		Vertex(glm::vec3(-0.5f, 0.5f, 0.5f),   glm::vec3(0.0f),  glm::vec3(1.0f),  glm::vec2(1.0f, 1.0f))      // upper right 4   #15
	};

	m_Indices.reserve(2 * 3 * 6);
	m_Indices =
	{
		// Front square
		0, 1, 2,
		1, 2, 3,
		// Right square
		4, 5, 6,
		5, 6, 7,
		// Back square
		8, 9, 10,
		9, 10, 11,
		// Left square
		12, 13, 14,
		13, 14, 15,
		// Top square
		2, 3, 10,
		2, 10, 11,
		// Bottom square
		0, 1, 8,
		0, 8, 9
	};
}

Cube::~Cube() {}
