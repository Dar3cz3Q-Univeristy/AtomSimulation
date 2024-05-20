#pragma once

#include <array>

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
	Shader m_DefaultCubeShader; // cube
	VertexArray m_VA;
	VertexBuffer m_VB;
	VertexArray m_cube_VA; // cube
	VertexBuffer m_cube_VB; // cube
	VertexBufferLayout m_Layout;
	IndexBuffer m_IB;
	IndexBuffer m_cube_IB; // cube
	//TextureCubeMap m_Texture;
	//Texture2D m_CubeTexture; // cube
	TextureCubeMap m_CubeTexture; // cube
	Renderer m_Renderer;
	Renderer m_CubeRenderer; // cube

	std::vector<Particle*> m_Particles;
	std::vector<Electron*> m_Electrons;

	void AddParticle(Particle* particle);
	void AddElectron(Electron* electron);
	void CreateCore(unsigned int count);
	void CreateElectrons(unsigned int count);
};

