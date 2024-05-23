#pragma once

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Buffer.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Textures/TextureFrameBuffer.h"

class PostProcessing
{
public:
	PostProcessing();
	~PostProcessing();

	void Draw(int filterID);
	void Update(int width, int height);

	void Bind() const;
	void Unbind() const;
private:
	int m_Width;
	int m_Height;
	float m_Gamma;

	Renderer m_Renderer;
	Shader m_Shader;
	VertexArray m_VA;
	VertexBuffer m_VB;
	IndexBuffer m_IB;
	VertexBufferLayout m_Layout;

	FrameBuffer m_FB;
	TextureFrameBuffer m_Texture;
	RenderBuffer m_RB;
	Buffer m_Buffer;
};

