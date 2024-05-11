#pragma once

class VertexBuffer {
public:
	VertexBuffer();
	~VertexBuffer();

	void Init(const void* data, unsigned int size);
	void Bind() const;
	void Unbind() const;
private:
	unsigned int m_RendererID;
};
