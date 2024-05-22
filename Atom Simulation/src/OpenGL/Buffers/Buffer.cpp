#include "Buffer.h"

Buffer::Buffer()
{
	m_Attachments.reserve(2);
}

Buffer::~Buffer() {}

void Buffer::Push(unsigned int glAttachment)
{
	m_Attachments.push_back(glAttachment);
}

void Buffer::Draw()
{
	GLCall(glDrawBuffers(m_Attachments.size(), m_Attachments.data()));
}

void Buffer::SaveCurrentFrameBuffer()
{
	GLCall(glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_CurrentBuffer));
}

void Buffer::RestorePreviousFrameBuffer()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_CurrentBuffer));
	m_CurrentBuffer = -1;
}
