#include "TextureMSAA.h"

TextureMSAA::TextureMSAA()
	: m_Samples(0)
{
	Create();
}

TextureMSAA::~TextureMSAA()
{
	Destroy();
}

void TextureMSAA::Create()
{
	GLCall(glGenTextures(1, &m_RendererID));
}

void TextureMSAA::Destroy()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureMSAA::Init(unsigned int samples, int width, int height)
{
	m_Samples = samples;
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID));
	GLCall(glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_Samples, GL_RGBA32F, width, height, GL_TRUE));
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_RendererID, 0));
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

void TextureMSAA::Update(int width, int height)
{
	Destroy();
	Create();
	Bind();
	Init(m_Samples, width, height);
}
