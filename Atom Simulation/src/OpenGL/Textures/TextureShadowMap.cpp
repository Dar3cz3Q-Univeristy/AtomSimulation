#include "TextureShadowMap.h"

TextureShadowMap::TextureShadowMap()
{
	Create();
}

TextureShadowMap::~TextureShadowMap()
{
	Destroy();
}

void TextureShadowMap::Create()
{
	GLCall(glGenTextures(1, &m_RendererID));
}

void TextureShadowMap::Destroy()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void TextureShadowMap::Init(int width, int height)
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

	float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor));
}

void TextureShadowMap::Update(int width, int height)
{

}

void TextureShadowMap::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_RendererID));
}

void TextureShadowMap::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0));
}

