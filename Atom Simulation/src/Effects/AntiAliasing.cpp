#include "AntiAliasing.h"

AntiAliasing::AntiAliasing(unsigned int samples) 
	: m_Width(WIDTH), m_Height(HEIGHT), m_Samples(samples)
{
	GLCall(glEnable(GL_MULTISAMPLE));

	m_FB.Bind();

	m_Texture.Init(m_Samples);

	m_RB.Bind();
	m_RB.Init(m_Samples);
}

AntiAliasing::~AntiAliasing() {}

void AntiAliasing::Read() const
{
	m_FB.Read();
}

void AntiAliasing::Update(int width, int height)
{
	if (width == m_Width && height == m_Height)
		return;

	if (width == 0 || height == 0)
		return;

	m_Width = width;
	m_Height = height;

	m_FB.Bind();
	m_RB.Update(m_Width, m_Height);
	m_Texture.Update(m_Width, m_Height);
}

void AntiAliasing::Bind() const
{
	m_FB.Bind();
}

void AntiAliasing::Unbind() const
{
	m_FB.Unbind();
}
