#pragma once

#include "Renderer.h"

class FrameBufferShadow
{
public:
	FrameBufferShadow();
	~FrameBufferShadow();

	void Init(unsigned int shadowTexture);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

