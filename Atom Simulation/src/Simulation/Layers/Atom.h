#pragma once

#include <array>
#include <unordered_map>

#include "Layer.h"
#include "Specification.h"

#include "Objects/Particle.h"
#include "Objects/Electron.h"
#include "Objects/DisplayCube.h"

class Atom : public Layer
{
public:
	Atom(GLFWwindow* window, Camera* camera);
	~Atom();

	void OnDraw() override;
	void OnUpdate() override;
 private:
	GLFWwindow* m_Window;
	Camera* m_Camera;
	Shader m_LightShader;

	// Cube
	Shader m_CubeShader;
	VertexArray m_CubeVA;
	VertexBuffer m_CubeVB;
	IndexBuffer m_CubeIB;
	TextureCubeMap m_CubeTexture;
	DisplayCube m_Cube;

	//Sphere
	Shader m_ParticleShader;
	VertexArray m_SphereVA;
	VertexBuffer m_SphereVB;
	IndexBuffer m_SphereIB;

	std::unordered_map<int, std::string> m_FileDataPointer;
	std::unordered_map<int, std::vector<Particle*>> m_Particles;
	std::unordered_map<int, std::vector<Electron*>> m_Electrons;

	void OnChange();
	void ChangeRenderData();
	void DownloadRenderData();
};

static int ElementID = 0;

void ChangeElement(GLFWwindow* window, int key, int scancode, int action, int mods);

