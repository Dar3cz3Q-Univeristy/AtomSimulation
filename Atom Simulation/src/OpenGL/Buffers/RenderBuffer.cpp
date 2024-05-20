#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
{
	Create();
}

RenderBuffer::~RenderBuffer()
{
	Destroy();
}

void RenderBuffer::Create()
{
	GLCall(glGenRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::Destroy()
{
	GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::Init(int width, int height)
{
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID));
}

void RenderBuffer::Bind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBuffer::Unbind() const
{
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

void RenderBuffer::Update(int width, int height)
{
	Destroy();
	Create();
	Bind();
	Init(width, height);
}
