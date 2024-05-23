#pragma once

#include "Renderer.h"

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();

	void Init(int width = WIDTH, int height = HEIGHT);
	void Update(int width, int height);

	void Bind() const;
	void Unbind() const;
private:
	void Create();
	void Destroy();
	unsigned int m_RendererID;
};

