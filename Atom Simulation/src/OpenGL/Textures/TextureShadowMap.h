#pragma once

#include "Texture.h"

class TextureShadowMap : public Texture
{
public:
	TextureShadowMap();
	~TextureShadowMap();

	operator unsigned int() const { return m_RendererID; };

	void Init(int width, int height);
	void Update(int width, int height);

	void Bind(unsigned int slot = 0) const override;
	void Unbind() const override;

	void SetViewPort();
	void RestoreViewPort();

	void SetWindowWidth(int width) { m_WindowWidth = width; };
	void SetWindowHeight(int height) { m_WindowHeight = height; };

	inline int GetWidth() const override { return 0; };
	inline int GetHeight() const override { return 0; };
private:
	void Create();
	void Destroy();
	unsigned int m_RendererID;
	unsigned int m_Samples;
	unsigned int m_Width, m_Height;
	unsigned int m_WindowWidth, m_WindowHeight;
};

