#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>

#include "Vertex.h"

class Sphere
{
public:
    Sphere(float radius, unsigned int rings, unsigned int sectors);
    ~Sphere();

    std::vector<Vertex>& GetVerticies() { return m_Vertices; };
    std::vector<unsigned int>& GetIndicies() { return m_Indices; };
private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
};

