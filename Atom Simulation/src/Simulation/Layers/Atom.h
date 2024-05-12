#pragma once

#include "Layer.h"
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

	std::vector<Particle*> m_Particles;
	std::vector<Electron*> m_Electrons;

	void AddParticle(Particle* particle);
	void AddElectron(Electron* electron);
	void CreateCore(unsigned int count);
	void CreateElectrons(unsigned int count);
};

