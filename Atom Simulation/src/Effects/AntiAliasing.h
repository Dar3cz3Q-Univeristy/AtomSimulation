#pragma once

#include "Renderer.h"
#include "Buffers/FrameBufferMSAA.h"
#include "Buffers/RenderBufferMSAA.h"
#include "Textures/TextureMSAA.h"

class AntiAliasing
{
public:
	AntiAliasing(unsigned int samples);
	~AntiAliasing();

	void Read() const;
	void Update(int width, int height);

	void Bind() const;
	void Unbind() const;
private:
	int m_Width;
	int m_Height;
	unsigned int m_Samples;

	Renderer m_Renderer;

	FrameBufferMSAA m_FB;
	TextureMSAA m_Texture;
	RenderBufferMSAA m_RB;
};

