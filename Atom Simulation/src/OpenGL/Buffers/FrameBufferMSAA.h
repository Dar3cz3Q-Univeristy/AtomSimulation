#pragma once

#include "Renderer.h"

class FrameBufferMSAA
{
public:
	FrameBufferMSAA();
	~FrameBufferMSAA();

	void Bind() const;
	void Unbind() const;
	void Read() const;
private:
	unsigned int m_RendererID;
};

