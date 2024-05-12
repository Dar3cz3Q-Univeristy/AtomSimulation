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
	m_VA.LinkAttribute(m_VB, 2, 2, GL_FLOAT, sizeof(Vertex));	// UV

	m_IB.Init(sphere.GetIndicies());

	m_LightShader.Init("res/shaders/light.vert.shader", "res/shaders/light.frag.shader");
	m_DefaultShader.Init("res/shaders/default.vert.shader", "res/shaders/default.frag.shader");

	// Creating core from particles based on sphere

	CreateCore(sphere.GetIndicies().size());

	// Creating moving electrons based on sphere

	CreateElectrons(sphere.GetIndicies().size());

	AS_LOG("Atom layer initialized");
}

Atom::~Atom() {
	for (auto& particle : m_Particles)
		if (particle) 
			delete particle;

	for (auto& electron : m_Electrons)
		if (electron)
			delete electron;
}

void Atom::OnDraw()
{
	m_VA.Bind();
	m_VB.Bind();

	m_DefaultShader.Bind();
	m_Camera->Matrix(m_DefaultShader, "u_VP");

	m_LightShader.Bind();
	m_Camera->Matrix(m_LightShader, "u_VP");

	int electronIndex = 0;

	std::vector<glm::vec3> electronsPosition;
	electronsPosition.reserve(m_Electrons.size());

	std::vector<glm::vec3> electronsColors;
	electronsColors.reserve(m_Electrons.size());

	for (auto& electron : m_Electrons) {
		electron->Draw(m_LightShader);

		// Save lights positions and colors to vector
		electronsPosition.push_back(electron->GetPosition());
		electronsColors.push_back(electron->GetColor());
	}

	// Update lights positions and colors
	m_DefaultShader.Bind();
	m_DefaultShader.SetUniform3fv("u_MultipleLightPos", electronsPosition);
	m_DefaultShader.SetUniform3fv("u_MultipleLightColor", electronsColors);

	// Draw Core
	for (auto& particle : m_Particles) {
		particle->Draw(m_DefaultShader);
	}
}

void Atom::OnUpdate()
{
	m_Camera->Inputs(m_Window);
}

void Atom::AddParticle(Particle* particle)
{
	m_Particles.push_back(particle);
}

void Atom::AddElectron(Electron* electron)
{
	m_Electrons.push_back(electron);
}

void Atom::CreateCore(unsigned int count)
{
	for (int i = 0; i < 5; i++) {
		Particle* temp = new Particle(PROTON, glm::vec3(1 * i, 0, 0), count);
		AddParticle(temp);
	}
}

void Atom::CreateElectrons(unsigned int count)
{
	Electron* temp1 = new Electron(glm::vec3(1, 0, 0), count, 5.0f, glm::vec3(0, 1, 1), glm::vec3(1, 0, 0));
	Electron* temp2 = new Electron(glm::vec3(.5, 0, 0), count, 3.0f, glm::vec3(0, 1, 1));
	Electron* temp3 = new Electron(glm::vec3(.7, 0, 0), count, 2.0f, glm::vec3(1, 0, 1));

	AddElectron(temp1);
	AddElectron(temp2);
	AddElectron(temp3);
}
