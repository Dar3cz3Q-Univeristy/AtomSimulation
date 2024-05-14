#pragma once

#include <vector>

class IndexBuffer {
public:
	IndexBuffer();
	~IndexBuffer();

	void Init(const unsigned int* data, unsigned int count);
	void Init(const std::vector<unsigned int>& data);
	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; };
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};
