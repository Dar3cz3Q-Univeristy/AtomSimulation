#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
	: m_Count(0)
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

void IndexBuffer::Init(const std::vector<unsigned int>& data)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	m_Count = static_cast<unsigned int>(data.size());

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data.data(), GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}
