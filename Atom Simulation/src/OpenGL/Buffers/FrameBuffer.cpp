#include "FrameBuffer.h"

FrameBuffer::FrameBuffer()
{
	GLCall(glGenFramebuffers(1, &m_RendererID));
}

FrameBuffer::~FrameBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void FrameBuffer::Bind() const
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_RendererID));
}

void FrameBuffer::Unbind() const
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void FrameBuffer::Draw() const
{
	GLCall(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_RendererID));
	GLCall(glBlitFramebuffer(0, 0, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, GL_COLOR_BUFFER_BIT, GL_NEAREST));
}
