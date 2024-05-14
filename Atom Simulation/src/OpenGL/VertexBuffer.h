#pragma once

#include <vector>

#include "Vertex.h"

class VertexBuffer 
{
public:
	VertexBuffer();
	~VertexBuffer();

	void Init(const void* data, unsigned int size);
	void Init(const std::vector<Vertex>& data);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};
