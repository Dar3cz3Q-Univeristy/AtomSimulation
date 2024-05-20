#include "AntiAliasing.h"

AntiAliasing::AntiAliasing(unsigned int samples) 
	: m_Samples(samples)
{
	GLCall(glEnable(GL_MULTISAMPLE));

	m_FB.Bind();

	m_Texture.Init(m_Samples);

	m_RB.Bind();
	m_RB.Init(m_Samples);
}

AntiAliasing::~AntiAliasing() {}

void AntiAliasing::Bind() const
{
	m_FB.Bind();
}

void AntiAliasing::Unbind() const
{
	m_FB.Unbind();
}

void AntiAliasing::Read() const
{
	m_FB.Read();
}
