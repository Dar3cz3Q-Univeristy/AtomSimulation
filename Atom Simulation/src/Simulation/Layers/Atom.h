#pragma once

#include <array>
#include <unordered_map>

#include "Layer.h"
#include "Specification.h"

#include "Objects/Particle.h"
#include "Objects/Electron.h"

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
	Shader m_DefaultShader;
	VertexArray m_VA;
	VertexBuffer m_VB;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IB;
	TextureCubeMap m_Texture;
	Renderer m_Renderer;

	//std::vector<Particle*> m_Particles;
	//std::vector<Electron*> m_Electrons;
	std::unordered_map<int, std::string> m_FileDataPointer;
	std::unordered_map<int, std::vector<Particle*>> m_Particles;
	std::unordered_map<int, std::vector<Electron*>> m_Electrons;

	void OnChange();
	void ChangeRenderData();
	void DownloadRenderData();
};

static int ElementID = 0;

void ChangeElement(GLFWwindow* window, int key, int scancode, int action, int mods);

