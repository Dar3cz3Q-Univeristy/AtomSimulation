#pragma once

#include <vector>

#include "Vertex.h"

class Cube
{
public:
    Cube();
    ~Cube();

    std::vector<Vertex>& GetVerticies() { return m_Vertices; };
    std::vector<unsigned int>& GetIndicies() { return m_Indices; };
private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
};

