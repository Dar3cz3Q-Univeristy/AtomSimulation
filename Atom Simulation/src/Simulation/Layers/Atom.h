#pragma once

#include <array>
#include <unordered_map>

#include "Layer.h"
#include "Specification.h"

#include "Buffer.h"
#include "Objects/Particle.h"
#include "Objects/Electron.h"
#include "Objects/DisplayCube.h"
#include "TextureShadowMap.h"
#include "FrameBufferShadow.h"

class Atom : public Layer
{
public:
	Atom(GLFWwindow* window, Camera* camera);
	~Atom();

	void DrawScene();
	void DrawShadow();
	void OnDraw() override;
	void OnUpdate() override;
	void OnResize(int width, int height) override;
 private:
	Renderer m_Renderer;
	GLFWwindow* m_Window;
	Camera* m_Camera;
	Buffer m_Buffer;

	// Shadows && Lights
	Shader m_ElectronShader;
	Shader m_ShadowShader;
	TextureShadowMap m_ShadowMap;
	FrameBufferShadow m_ShadowFB;
	glm::mat4 m_LightProjection;

	// Cube
	Shader m_CubeShader;
	VertexArray m_CubeVA;
	VertexBuffer m_CubeVB;
	IndexBuffer m_CubeIB;
	DisplayCube m_Cube;

	//Sphere
	Shader m_ParticleShader;
	VertexArray m_SphereVA;
	VertexBuffer m_SphereVB;
	IndexBuffer m_SphereIB;

	std::unordered_map<int, std::string> m_FileDataPointer;
	std::unordered_map<int, std::vector<Particle*>> m_Particles;
	std::unordered_map<int, std::vector<Electron*>> m_Electrons;
	std::unordered_map<int, Texture2D> m_CubeTextures;

	void OnChange();
	void ChangeRenderData();
	void DownloadRenderData();
};