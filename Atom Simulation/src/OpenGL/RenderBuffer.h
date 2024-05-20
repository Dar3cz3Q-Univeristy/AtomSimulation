#pragma once

#include "Renderer.h"

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();

	void Bind() const;
	void Unbind() const;
	void Init() const;
private:
	unsigned int m_RendererID;
};

