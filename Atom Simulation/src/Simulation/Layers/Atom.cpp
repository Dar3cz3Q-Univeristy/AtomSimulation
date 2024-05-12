#include "Atom.h"

Atom::Atom(GLFWwindow* window, Camera* camera)
	: m_Window(nullptr), m_Camera(nullptr)
{
	m_Window = window;
	m_Camera = camera;
}

Atom::~Atom() {}

void Atom::OnDraw()
{
	m_Camera->Matrix(m_Shader, "u_MVP");

	m_Renderer.Draw(m_VA, m_IB, m_Shader);
}

void Atom::OnUpdate()
{
	m_Camera->Inputs(m_Window);
}
