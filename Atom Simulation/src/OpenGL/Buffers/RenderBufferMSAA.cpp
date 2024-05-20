#include "RenderBufferMSAA.h"

RenderBufferMSAA::RenderBufferMSAA()
	: m_Samples(0)
{
	Create();
}

RenderBufferMSAA::~RenderBufferMSAA()
{
	Destroy();
}

void RenderBufferMSAA::Create()
{
	GLCall(glGenRenderbuffers(1, &m_RendererID));
}

void RenderBufferMSAA::Destroy()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBufferMSAA::Init(unsigned int samples, int width, int height)
{
	m_Samples = samples;
	GLCall(glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_Samples, GL_DEPTH24_STENCIL8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID));
}

void RenderBufferMSAA::Update(int width, int height)
{
	Destroy();
	Create();
	Bind();
	Init(m_Samples, width, height);
}

void RenderBufferMSAA::Bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBufferMSAA::Unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}