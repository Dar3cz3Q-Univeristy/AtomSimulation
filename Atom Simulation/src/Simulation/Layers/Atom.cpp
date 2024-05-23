#include "Atom.h"
#include "Global.h"

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
	m_ElectronShader.Init("res/shaders/electron.vert.shader", "res/shaders/electron.frag.shader");

	SPHERE_INDICIES_COUNT = static_cast<unsigned int>(sphere.GetIndicies().size());

	//
	// Creating cube
	//

	Cube cube;

	m_CubeVB.Init(cube.GetVerticies());

	m_CubeVA.LinkAttribute(m_CubeVB, 0, 3, GL_FLOAT, sizeof(Vertex));		// Position
	m_CubeVA.LinkAttribute(m_CubeVB, 1, 2, GL_FLOAT, sizeof(Vertex), 9);	// texCoords

	m_CubeShader.Init("res/shaders/cube_texture.vert.shader", "res/shaders/cube_texture.frag.shader");

	m_CubeIB.Init(cube.GetIndicies());

	m_CubeShader.Bind();

	m_CubeShader.SetUniform1i("u_Texture", 0);

	CUBE_INDICIES_COUNT = static_cast<unsigned int>(cube.GetIndicies().size());

	//
	// Specify file location for render data
	//

	m_FileDataPointer[0] = "Test.aselement";
	m_FileDataPointer[1] = "Aluminium.aselement";
	m_FileDataPointer[2] = "Argon.aselement";
	m_FileDataPointer[3] = "Beryllium.aselement";
	m_FileDataPointer[4] = "Boron.aselement";
	m_FileDataPointer[5] = "Calcium.aselement";
	m_FileDataPointer[6] = "Carbon.aselement";
	m_FileDataPointer[7] = "Chlorine.aselement";
	m_FileDataPointer[8] = "Copernicium.aselement";
	m_FileDataPointer[9] = "Fluorine.aselement";
	m_FileDataPointer[10] = "Gold.aselement";
	m_FileDataPointer[11] = "Helium.aselement";
	m_FileDataPointer[12] = "Hydrogen.aselement";
	m_FileDataPointer[13] = "Lithium.aselement";
	m_FileDataPointer[14] = "Magnesium.aselement";
	m_FileDataPointer[15] = "Neon.aselement";
	m_FileDataPointer[16] = "Nitrogen.aselement";
	m_FileDataPointer[17] = "Oxygen.aselement";
	m_FileDataPointer[18] = "Phosphorus.aselement";
	m_FileDataPointer[19] = "Platinium.aselement";
	m_FileDataPointer[20] = "Polonium.aselement";
	m_FileDataPointer[21] = "Silicon.aselement";
	m_FileDataPointer[22] = "Silver.aselement";
	m_FileDataPointer[23] = "Sodium.aselement";
	m_FileDataPointer[24] = "Sulfur.aselement";

	DownloadRenderData();

	//
	//	Shadows
	//

	m_ShadowShader.Init("res/shaders/shadow.vert.shader", "res/shaders/shadow.frag.shader");

	int shadowWidth = 2048, shadowHeight = 2048;

	m_ShadowMap.Init(shadowWidth, shadowHeight);

	int windowWidth, windowHeight;
	glfwGetWindowSize(m_Window, &windowWidth, &windowHeight);

	m_ShadowMap.SetWindowWidth(windowWidth);
	m_ShadowMap.SetWindowHeight(windowHeight);

	m_ShadowFB.Init(m_ShadowMap);

	glm::vec3 lightPos = m_Cube.GetPosition();

	float aspect = (float)shadowWidth / (float)shadowHeight;
	float near = 1.0f;
	float far = 25.0f;

	glm::mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), aspect, near, far);
	glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	m_LightProjection = perspectiveProjection * lightView;

	m_ShadowShader.Bind();
	m_ShadowShader.SetUniformMat4f("u_LightProjection", m_LightProjection);

	m_ParticleShader.Bind();
	m_ParticleShader.SetUniform3f("u_LightPosition", lightPos.x, lightPos.y, lightPos.z);
	m_ParticleShader.SetUniformMat4f("u_LightProjection", m_LightProjection);

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
	// Update uniforms
	m_ParticleShader.Bind();

	m_ShadowMap.Bind();
	m_ParticleShader.SetUniform1i("u_ShadowMap", 0);

	m_Camera->Matrix(m_ElectronShader, "u_VP");
	m_Camera->Matrix(m_ParticleShader, "u_VP");
	m_Camera->Position(m_ParticleShader, "u_CamPos");

	m_CubeShader.Bind();
	m_Camera->Matrix(m_CubeShader, "u_VP");

	// Draw particles
	m_SphereVA.Bind();
	m_SphereVB.Bind();

	// Draw electrons
	for (auto& electron : m_Electrons[ElementID])
		electron->Draw(m_ElectronShader);

	// Draw particles
	for (auto& particle : m_Particles[ElementID])
		particle->Draw(m_ParticleShader);

	// Draw Cube
	m_CubeTextures[ElementID].Bind();
	m_CubeVA.Bind();
	m_CubeIB.Bind();
	m_Cube.Draw(m_CubeShader);
}

void Atom::DrawShadow()
{
	// Prepare shadow buffer
	m_Buffer.SaveCurrentFrameBuffer();

	m_ShadowMap.SetViewPort();
	m_ShadowFB.Bind();
	m_Renderer.Clear();

	// Draw scene using shadow shader
	m_SphereVA.Bind();
	m_SphereVB.Bind();

	for (auto& electron : m_Electrons[ElementID])
		electron->Draw(m_ShadowShader);

	for (auto& particle : m_Particles[ElementID])
		particle->Draw(m_ShadowShader);

	m_CubeTextures[ElementID].Bind();
	m_CubeVA.Bind();
	m_CubeIB.Bind();
	m_Cube.Draw(m_ShadowShader);

	// Restore previous settings
	m_ShadowFB.Unbind();
	m_ShadowMap.RestoreViewPort();
	m_Renderer.Clear();
	m_Buffer.RestorePreviousFrameBuffer();
}

void Atom::OnDraw()
{
	// Draw Shadow to Shadowe buffer
	DrawShadow();

	m_Renderer.Clear();

	//Draw Actual Scene to Antialiasing buffer
	DrawScene();

	// Check if ElementID has changed
	OnChange();
}

void Atom::OnUpdate()
{
	m_Camera->Inputs(m_Window);
}

void Atom::OnResize(int width, int height)
{
	m_ShadowMap.Update(width, height);
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

	m_CubeTextures[ElementID].Init("res/textures/atom/" + tempTexture + "");

	stream.close();
}