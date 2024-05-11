#pragma once
#include "Layer.h"

class Example : public Layer
{
public:
	Example(GLFWwindow* window);
	~Example();

	void OnDraw() override;
	void OnUpdate() override;
private:
	GLFWwindow* m_Window;
	Camera m_Camera;
	Shader m_Shader;
	VertexArray m_VA;
	VertexBuffer m_VB;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IB;
	TextureCubeMap m_Texture;
	Renderer m_Renderer;
};

