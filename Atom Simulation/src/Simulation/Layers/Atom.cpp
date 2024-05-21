#include "Atom.h"
#include "Objects/Template/Sphere.h"
#include "Objects/Template/Cube.h"

Atom::Atom(GLFWwindow* window, Camera* camera)
	: m_Window(nullptr), m_Camera(nullptr)
{
	m_Window = window;
	m_Camera = camera;
	
	//
	// Creating sphere
	//

	Sphere sphere(0.5f, 64, 64);

	m_SphereVB.Init(sphere.GetVerticies());

	m_SphereVA.LinkAttribute(m_SphereVB, 0, 3, GL_FLOAT, sizeof(Vertex));	// Position
	m_SphereVA.LinkAttribute(m_SphereVB, 1, 3, GL_FLOAT, sizeof(Vertex));	// Normal
	m_SphereVA.LinkAttribute(m_SphereVB, 2, 2, GL_FLOAT, sizeof(Vertex));	// UV

	m_SphereIB.Init(sphere.GetIndicies());

	m_ParticleShader.Init("res/shaders/default.vert.shader", "res/shaders/default.frag.shader");

	SPHERE_INDICIES_COUNT = static_cast<unsigned int>(sphere.GetIndicies().size());

	//
	// Creating cube
	//

	Cube cube;

	m_CubeVB.Init(cube.GetVerticies());

	m_CubeVA.LinkAttribute(m_CubeVB, 0, 3, GL_FLOAT, sizeof(Vertex));		// Position

#if 1
	m_CubeVA.LinkAttribute(m_CubeVB, 1, 2, GL_FLOAT, sizeof(Vertex), 9);	// texCoords
	m_CubeShader.Init("res/shaders/cube_texture.vert.shader", "res/shaders/cube_texture.frag.shader");
#else
	m_CubeVA.LinkAttribute(m_CubeVB, 1, 3, GL_FLOAT, sizeof(Vertex), 6);	// Colors
	m_CubeShader.Init("res/shaders/cube_default.vert.shader", "res/shaders/cube_default.frag.shader");
#endif

	m_CubeIB.Init(cube.GetIndicies());

	m_CubeShader.Bind();

	m_CubeShader.SetUniform1i("u_Texture", 0);

	CUBE_INDICIES_COUNT = static_cast<unsigned int>(cube.GetIndicies().size());

	//
	// Specify file location for render data
	//

	m_FileDataPointer[0] = "Magnesium.aselement";
	m_FileDataPointer[1] = "Calcium.aselement";
	m_FileDataPointer[2] = "Silver.aselement";
	m_FileDataPointer[3] = "Platinium.aselement";

	DownloadRenderData();

	//
	//	Shadows
	//

	m_ShadowShader.Init("res/shaders/shadow.vert.shader", "res/shaders/shadow.frag.shader");

	//m_ShadowMap.Init(2480, 2480);
	//m_ShadowFB.Init(m_ShadowMap);

	glm::vec3 lightPos(50.0f, 50.0f, 50.0f);

	glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);
	glm::mat4 lightView = glm::lookAt(20.0f * lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightProjection = orthgonalProjection * lightView;

	//m_ShadowShader.Bind();
	//m_ShadowShader.SetUniformMat4f("u_LightProjection", lightProjection);

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

void Atom::DrawScene()
{
	// Update View, Projection matricies and other uniforms
	m_ParticleShader.Bind();

	glm::vec3 cubePos = m_Cube.GetPosition();
	m_ParticleShader.SetUniform3f("u_LightPosition", cubePos.x, cubePos.y, cubePos.z);

	m_Camera->Position(m_ParticleShader, "u_CamPos");
	m_Camera->Matrix(m_ParticleShader, "u_VP");

	m_CubeShader.Bind();
	m_Camera->Matrix(m_CubeShader, "u_VP");

	m_SphereVA.Bind();
	m_SphereVB.Bind();

	// Draw electrons
	for (auto& electron : m_Electrons[ElementID])
		electron->Draw(m_ParticleShader);

	// Draw Core
	for (auto& particle : m_Particles[ElementID])
		particle->Draw(m_ParticleShader);

	// Draw Cube
	m_CubeTextures[ElementID].Bind();
	m_CubeVA.Bind();
	m_CubeIB.Bind();
	m_Cube.Draw(m_CubeShader);
}

void Atom::OnDraw()
{
	DrawScene();

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

	m_CubeTextures[ElementID].Init("res/textures/elements/" + tempTexture + "");

	stream.close();
}

void ChangeElement(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
		ElementID = (ElementID + 1) % ELEMENTS_COUNT;
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
		ElementID = (ElementID == 0 ? ELEMENTS_COUNT - 1 : ElementID - 1);
}
