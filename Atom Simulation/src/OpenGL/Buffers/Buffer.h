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
	void SaveCurrentFrameBuffer();
	void RestorePreviousFrameBuffer();
private:
	int m_CurrentBuffer;
	std::vector<unsigned int> m_Attachments;
};

