#pragma once

#include "Texture.h"

class TextureFrameBuffer : public Texture
{
public:
	TextureFrameBuffer();
	~TextureFrameBuffer();

	void Init(int width = WIDTH, int height = HEIGHT);
	void Update(int width, int height);

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	inline int GetWidth() const override { return 0; };
	inline int GetHeight() const override { return 0; };
private:
	void Create();
	void Destroy();
	unsigned int m_RendererID;
};

