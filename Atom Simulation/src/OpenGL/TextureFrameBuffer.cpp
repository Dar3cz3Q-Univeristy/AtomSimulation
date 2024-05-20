#include "TextureFrameBuffer.h"

TextureFrameBuffer::TextureFrameBuffer()
{
	GLCall(glGenTextures(1, &m_RendererID));
}

TextureFrameBuffer::~TextureFrameBuffer()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureFrameBuffer::Bind(unsigned int slot) const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void TextureFrameBuffer::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void TextureFrameBuffer::Init() const
{
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RendererID, 0));
}
