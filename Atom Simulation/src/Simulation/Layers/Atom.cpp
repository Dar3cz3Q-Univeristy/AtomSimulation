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

	m_cube_VA.Bind();

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
	SPHERE_INDICIES_COUNT = static_cast<unsigned int>(sphere.GetIndicies().size());

	//
	// Specify file location for render data
	//
	m_FileDataPointer[0] = "Magnesium.aselement";
	m_FileDataPointer[1] = "Calcium.aselement";
	m_FileDataPointer[2] = "Silver.aselement";
	m_FileDataPointer[3] = "Platinium.aselement";

	DownloadRenderData();

	glfwSetKeyCallback(m_Window, ChangeElement);

	AS_LOG("Atom layer initialized");
}

Atom::~Atom() {
	for (auto& particleVector : m_Particles) for (auto& particle : particleVector.second)
		if (particle)
			delete particle;

	for (auto& electronVector : m_Electrons) for (auto& electron : electronVector.second)
		if (electron)
			delete electron;
}

void Atom::OnDraw()
{
	m_VA.Bind();
	m_VB.Bind();

	m_DefaultShader.Bind();
	m_Camera->Matrix(m_DefaultShader, "u_VP");
	m_DefaultShader.SetUniform1i("u_ElectronCount", static_cast<int>(m_Electrons[ElementID].size()));

	m_LightShader.Bind();
	m_Camera->Matrix(m_LightShader, "u_VP");

	std::array<glm::vec3, MAX_ELECTRON_COUNT> electronsPosition{};
	std::array<glm::vec3, MAX_ELECTRON_COUNT> electronsColors{};

	int counter = 0;

	for (auto& electron : m_Electrons[ElementID])
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
	for (auto& particle : m_Particles[ElementID])
		particle->Draw(m_DefaultShader);

	// Draw Cube
	m_DefaultCubeShader.Bind();
	//m_CubeTexture.Bind();

	m_Camera->Matrix(m_DefaultCubeShader, "u_MVP");

	m_Renderer.Draw(m_cube_VA, m_cube_IB, m_DefaultCubeShader);

	// Check if ElementID has changed
	OnChange();
}

void Atom::OnUpdate()
{
	m_Camera->Inputs(m_Window);
}

void Atom::OnChange()
{
	static int lastID = ElementID;

	if (lastID != ElementID) {
		lastID = ElementID;
		ChangeRenderData();
	}
}

void Atom::ChangeRenderData()
{
	if (m_Particles[ElementID].empty())
		DownloadRenderData();
}

void Atom::DownloadRenderData()
{
	// TODO: This probably should be better written :)
	// Parsing data to render elements. 

	std::ifstream stream("res/elements/" + m_FileDataPointer[ElementID] + "");

	if (!stream) {
		std::cout << "Error file: " << m_FileDataPointer[ElementID] << " doesn't exists!" << std::endl;
		stream.close();
		return;
	}

	std::string line;
	size_t currentIndex = 0;

	std::string tempTexture;

	char type = -1;

	while (getline(stream, line)) {
		if (line.find("#texture") != std::string::npos) {
			currentIndex = line.find("=") + 1;
			tempTexture = line.substr(currentIndex);
			continue;
		}

		if (line.find("#particles") != std::string::npos) {
			type = 1;
			continue;
		}

		if (line.find("#electrons") != std::string::npos) {
			type = 2;
			continue;
		}

		// Extract position
		glm::vec3 position;

		currentIndex = line.find("x=") + 2;
		position.x = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

		currentIndex = line.find("y=") + 2;
		position.y = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

		currentIndex = line.find("z=") + 2;
		position.z = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

		// Extract scale
		float scale = 0.0f;

		currentIndex = line.find("scale=") + 6;
		scale = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

		if (type == 1) {
			// Extract Type
			currentIndex = line.find("type=") + 5;
			std::string typeString = line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex);

			ParticleType type;
			if (typeString == "PROTON") {
				type = PROTON;
			}
			else if (typeString == "NEUTRON") {
				type = NEUTRON;
			}
			
			// Create particle
			m_Particles[ElementID].push_back(new Particle(type, position, scale));

			continue;
		} 

		if (type == 2) {
			// Extract angular speed
			float angularSpeed = 0.0f;

			currentIndex = line.find("speed=") + 6;
			angularSpeed = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

			// Extract rotation axis
			glm::vec3 axis;

			currentIndex = line.find("axis_x=") + 7;
			axis.x = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

			currentIndex = line.find("axis_y=") + 7;
			axis.y = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

			currentIndex = line.find("axis_z=") + 7;
			axis.z = std::stof(line.substr(currentIndex, line.find(" ", currentIndex) - currentIndex));

			// Create electron
			m_Electrons[ElementID].push_back(new Electron(position, scale, angularSpeed, axis));

			continue;
		}
	}

	stream.close();
}

void ChangeElement(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		ElementID = (ElementID + 1) % ELEMENTS_COUNT;
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		ElementID = (ElementID == 0 ? ELEMENTS_COUNT - 1 : ElementID - 1);
}
