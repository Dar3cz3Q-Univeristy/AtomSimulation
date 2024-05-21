#pragma once

#include "Texture.h"

class TextureMSAA : public Texture
{
public:
	TextureMSAA();
	~TextureMSAA();

	void Init(unsigned int samples, int width = WIDTH, int height = HEIGHT);
	void Update(int width, int height);

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	inline int GetWidth() const override { return 0; };
	inline int GetHeight() const override { return 0; };
private:
	void Create();
	void Destroy();
	unsigned int m_RendererID;
	unsigned int m_Samples;
};

