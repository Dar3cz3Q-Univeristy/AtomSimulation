#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));	
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Init(const unsigned int* data, unsigned int count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	m_Count = count;

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}