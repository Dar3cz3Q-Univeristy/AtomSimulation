#pragma once

#include "Renderer.h"

class RenderBufferMSAA
{
public:
	RenderBufferMSAA();
	~RenderBufferMSAA();

	void Bind() const;
	void Unbind() const;
	void Init(unsigned int samples);
private:
	unsigned int m_RendererID;
	unsigned int m_Samples;
};

