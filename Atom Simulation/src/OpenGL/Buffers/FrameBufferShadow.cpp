#include "FrameBufferShadow.h"

FrameBufferShadow::FrameBufferShadow()
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
}

FrameBufferShadow::~FrameBufferShadow()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void FrameBufferShadow::Init(unsigned int shadowTexture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture, 0);
	
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferShadow::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBufferShadow::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
