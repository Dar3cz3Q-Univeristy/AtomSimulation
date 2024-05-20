#include "TextureMSAA.h"

TextureMSAA::TextureMSAA()
	: m_Samples(0)
{
	GLCall(glGenTextures(1, &m_RendererID));
}

TextureMSAA::~TextureMSAA()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureMSAA::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID));
}

void TextureMSAA::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));
}

void TextureMSAA::Init(unsigned int samples)
{
	m_Samples = samples;
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID));
	GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Samples, GL_SRGB, WIDTH, HEIGHT, GL_TRUE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_RendererID, 0));
}
