#include "Atom.h"
#include "Objects/Sphere.h"

Atom::Atom(GLFWwindow* window, Camera* camera)
	: m_Window(nullptr), m_Camera(nullptr)
{
	m_Window = window;
	m_Camera = camera;

	Sphere sphere(0.5f, 64, 64);

	m_VB.Init(sphere.GetVerticies());

	m_VA.LinkAttribute(m_VB, 0, 3, GL_FLOAT, sizeof(Vertex));	// Position
	m_VA.LinkAttribute(m_VB, 1, 3, GL_FLOAT, sizeof(Vertex));	// Normal
	m_VA.LinkAttribute(m_VB, 2, 3, GL_FLOAT, sizeof(Vertex));	// Color
	m_VA.LinkAttribute(m_VB, 3, 2, GL_FLOAT, sizeof(Vertex));	// UV

	m_IB.Init(sphere.GetIndicies());

	m_Shader.Init("res/shaders/sphere.vert.shader", "res/shaders/sphere.frag.shader");
	m_Shader.Bind();

	AS_LOG("Atom layer initialized");
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
