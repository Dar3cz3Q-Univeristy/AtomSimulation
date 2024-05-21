#include "TextureFrameBuffer.h"

TextureFrameBuffer::TextureFrameBuffer()
{
	Create();
}

TextureFrameBuffer::~TextureFrameBuffer()
{
	Destroy();
}

void TextureFrameBuffer::Create()
{
	GLCall(glGenTextures(1, &m_RendererID));
}

void TextureFrameBuffer::Destroy()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureFrameBuffer::Init(int attachment, int width, int height)
{
	m_Attachment = attachment;
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_Attachment, GL_TEXTURE_2D, m_RendererID, 0));
}

void TextureFrameBuffer::Update(int width, int height)
{
	Destroy();
	Create();
	Bind();
	Init(m_Attachment, width, height);
}

void TextureFrameBuffer::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void TextureFrameBuffer::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

