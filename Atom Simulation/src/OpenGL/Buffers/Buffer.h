#pragma once

#include <vector>
#include "Renderer.h"

class Buffer
{
public:
	Buffer();
	~Buffer();

	void Push(unsigned int glAttachment);
	void Draw();
private:
	std::vector<unsigned int> m_Attachments;
};

