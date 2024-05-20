#pragma once

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "TextureFrameBuffer.h"

class PostProcessing
{
public:
	PostProcessing();
	~PostProcessing();

	void Bind() const;
	void Unbind() const;
	void Draw() const;
private:
	Renderer m_Renderer;
	Shader m_Shader;
	VertexArray m_VA;
	VertexBuffer m_VB;
	IndexBuffer m_IB;
	VertexBufferLayout m_Layout;

	FrameBuffer m_FB;
	TextureFrameBuffer m_Texture;
	RenderBuffer m_RB;

	float m_Gamma;
};

