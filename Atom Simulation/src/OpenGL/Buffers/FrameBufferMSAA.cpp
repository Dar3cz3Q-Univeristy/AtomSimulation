#include "FrameBufferMSAA.h"

FrameBufferMSAA::FrameBufferMSAA()
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
}

FrameBufferMSAA::~FrameBufferMSAA()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void FrameBufferMSAA::Bind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBufferMSAA::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBufferMSAA::Read() const
{
	GLCall(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_RendererID))
}
