#include "Atom.h"
#include "Objects/Sphere.h"

Atom::Atom(GLFWwindow* window, Camera* camera)
	: m_Window(nullptr), m_Camera(nullptr)
{
	m_Window = window;
	m_Camera = camera;


	Vertex verticies[] =
	{
		Vertex(glm::vec3(-0.5f, 2.0f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),       // lower left near 0
		Vertex(glm::vec3(0.5f, 2.0f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),        // lower right near 1
		Vertex(glm::vec3(-0.5f, 2.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower left far 2
		Vertex(glm::vec3(0.5f,  2.0f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec2(0.0f)),      // lower right far 3
		Vertex(glm::vec3(-0.5f, 3.0f, 0.5f), glm::vec3(0.98f, 0.72f, 0.01f), glm::vec3(0.0f), glm::vec2(0.0f)),     // upper left near 4
		Vertex(glm::vec3(0.5f, 3.0f, 0.5f), glm::vec3(0.94f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),      // upper right near 5
		Vertex(glm::vec3(-0.5f, 3.0f, -0.5f), glm::vec3(0.01f, 0.98f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f)),    // upper left far 6
		Vertex(glm::vec3(0.5f, 3.0f, -0.5f), glm::vec3(0.58f, 0.01f, 0.98f), glm::vec3(0.0f), glm::vec2(0.0f))      // upper right far 7
	};

	unsigned int indices[] =
	{
		// bottom square
		0, 1, 2,
		2, 1, 3,
		// near square
		0, 4, 5,
		0, 1, 5,
		// left square
		0, 2, 4,
		2, 4, 6,
		// far square
		2, 6, 3,
		3, 6, 7,
		// right square
		1, 3, 7,
		1, 5, 7,
		// top square
		4, 5, 6,
		5, 6, 7
	};


	Sphere sphere(0.5f, 64, 64);

	m_VB.Init(sphere.GetVerticies());

	m_VA.LinkAttribute(m_VB, 0, 3, GL_FLOAT, sizeof(Vertex));	// Position
	m_VA.LinkAttribute(m_VB, 1, 3, GL_FLOAT, sizeof(Vertex));	// Normal
	m_VA.LinkAttribute(m_VB, 2, 2, GL_FLOAT, sizeof(Vertex));	// UV

	m_IB.Init(sphere.GetIndicies());

	m_LightShader.Init("res/shaders/light.vert.shader", "res/shaders/light.frag.shader");
	m_DefaultShader.Init("res/shaders/default.vert.shader", "res/shaders/default.frag.shader");

	// Cube

	//m_cube_VA.Bind();

	m_cube_VB.Init(verticies, sizeof(verticies));
	//m_cube_VB.Bind();
	m_cube_IB.Init(indices, sizeof(indices));

	m_cube_VA.LinkAttribute(m_cube_VB, 0, 3, GL_FLOAT, sizeof(Vertex));

	//m_DefaultCubeShader.Init("res/shaders/cube_default.vert.shader", "res/shaders/cube_default.frag.shader");
	m_DefaultCubeShader.Init("res/shaders/cube_texture.vert.shader", "res/shaders/cube_texture.frag.shader");
	m_DefaultCubeShader.Bind();

	//m_CubeTexture.Init("res/textures/rubiks/back.png");
	m_CubeTexture.Init("res/textures/rubiks", "png");
	m_CubeTexture.Bind();

	m_DefaultCubeShader.SetUniform1i("u_Texture", 0);

	// Creating core from particles based on sphere

	unsigned int indicesSize = static_cast<unsigned int>(sphere.GetIndicies().size());

	CreateCore(indicesSize);

	// Creating moving electrons based on sphere

	CreateElectrons(indicesSize);

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

	std::array<glm::vec3, ELECTRON_COUNT> electronsPosition{};
	std::array<glm::vec3, ELECTRON_COUNT> electronsColors{};

	int counter = 0;

	for (auto& electron : m_Electrons) 
	{
		electron->Draw(m_LightShader);

		electronsPosition[counter] = electron->GetPosition();
		electronsColors[counter] = electron->GetColor();

		counter++;
	}

	// Update lights positions and colors
	m_DefaultShader.Bind();
	m_DefaultShader.SetUniform3fv("u_MultipleLightPos", electronsPosition);
	m_DefaultShader.SetUniform3fv("u_MultipleLightColor", electronsColors);

	// Draw Core
	for (auto& particle : m_Particles)
		particle->Draw(m_DefaultShader);

	// Draw Cube
	m_DefaultCubeShader.Bind();
	//m_CubeTexture.Bind();

	m_Camera->Matrix(m_DefaultCubeShader, "u_MVP");

	m_Renderer.Draw(m_cube_VA, m_cube_IB, m_DefaultCubeShader);
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
	for (int i = 0; i < 1; i++) 
	{
		Particle* temp = new Particle(PROTON, glm::vec3(1 * i, 0, 0), 0.3f, count);
		AddParticle(temp);
	}
}

void Atom::CreateElectrons(unsigned int count)
{
	// Keep number of electrons up to date in Specification.h and default.frag.shader
	Electron* temp1 = new Electron(glm::vec3(1, 0, 0), .2f, 100.0f, glm::vec3(0, 1, 1), count, glm::vec3(0, 1, 0));
	Electron* temp2 = new Electron(glm::vec3(.5, 0, 0), .2f, 30.0f, glm::vec3(0, 1, 1), count);
	Electron* temp3 = new Electron(glm::vec3(.7, 0, 0), .2f, 20.0f, glm::vec3(1, 0, 1), count);

	AddElectron(temp1);
	AddElectron(temp2);
	AddElectron(temp3);
}
