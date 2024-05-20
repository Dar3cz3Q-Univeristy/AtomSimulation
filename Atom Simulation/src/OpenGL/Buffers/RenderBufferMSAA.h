#pragma once

#include "Renderer.h"

class RenderBufferMSAA
{
public:
	RenderBufferMSAA();
	~RenderBufferMSAA();

	void Bind() const;
	void Unbind() const;

	void Init(unsigned int samples, int width = WIDTH, int height = HEIGHT);
	void Update(int width, int height);
private:
	void Create();
	void Destroy();
	unsigned int m_RendererID;
	unsigned int m_Samples;
};

