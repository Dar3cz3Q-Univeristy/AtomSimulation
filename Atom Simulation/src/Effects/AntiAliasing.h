#pragma once

#include "Renderer.h"
#include "FrameBufferMSAA.h"
#include "RenderBufferMSAA.h"
#include "TextureMSAA.h"

class AntiAliasing
{
public:
	AntiAliasing(unsigned int samples);
	~AntiAliasing();

	void Bind() const;
	void Unbind() const;
	void Read() const;
private:
	Renderer m_Renderer;

	FrameBufferMSAA m_FB;
	TextureMSAA m_Texture;
	RenderBufferMSAA m_RB;
private:
	unsigned int m_Samples;
};

