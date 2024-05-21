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
