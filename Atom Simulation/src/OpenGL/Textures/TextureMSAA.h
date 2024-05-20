#pragma once

#include "Texture.h"

class TextureMSAA : public Texture
{
public:
	TextureMSAA();
	~TextureMSAA();

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;
	inline int GetWidth() const override { return 0; };
	inline int GetHeight() const override { return 0; };
	void Init(unsigned int samples);
private:
	unsigned int m_RendererID;
	unsigned int m_Samples;
};

