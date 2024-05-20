#include "RenderBufferMSAA.h"

RenderBufferMSAA::RenderBufferMSAA()
	: m_Samples(0)
{
	GLCall(glGenRenderbuffers(1, &m_RendererID));
}

RenderBufferMSAA::~RenderBufferMSAA()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBufferMSAA::Bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBufferMSAA::Unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

void RenderBufferMSAA::Init(unsigned int samples)
{
	m_Samples = samples;
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_Samples, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID));
}
