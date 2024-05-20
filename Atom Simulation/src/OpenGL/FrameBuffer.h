#pragma once

#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

