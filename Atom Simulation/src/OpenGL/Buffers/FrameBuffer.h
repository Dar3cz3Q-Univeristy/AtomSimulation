#pragma once

#include "Renderer.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void Draw(int width, int height) const;

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};

