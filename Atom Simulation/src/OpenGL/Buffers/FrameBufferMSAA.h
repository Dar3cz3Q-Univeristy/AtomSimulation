#pragma once

#include "Renderer.h"

class FrameBufferMSAA
{
public:
	FrameBufferMSAA();
	~FrameBufferMSAA();

	void Read() const;

	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};