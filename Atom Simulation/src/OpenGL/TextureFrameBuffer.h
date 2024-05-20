#pragma once

#include "Texture.h"

class TextureFrameBuffer : public Texture
{
public:
	TextureFrameBuffer();
	~TextureFrameBuffer();

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;
	inline int GetWidth() const override { return 0; };
	inline int GetHeight() const override { return 0; };
	void Init() const;
private:
	unsigned int m_RendererID;
};

