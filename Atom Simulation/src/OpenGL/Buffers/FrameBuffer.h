#pragma once

#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;
	void Draw() const;
private:
	unsigned int m_RendererID;
};

