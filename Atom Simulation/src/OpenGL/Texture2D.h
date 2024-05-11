#pragma once
#include "Texture.h"

class Texture2D : public Texture
{
public:
	Texture2D();
	~Texture2D();

	void Init(const std::string& filepath);
	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	inline int GetWidth() const override { return m_Width; };
	inline int GetHeight() const override { return m_Height; };
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
};

