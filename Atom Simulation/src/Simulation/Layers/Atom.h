#pragma once

#include "Layer.h"

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
	Shader m_Shader;
	VertexArray m_VA;
	VertexBuffer m_VB;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IB;
	TextureCubeMap m_Texture;
	Renderer m_Renderer;
};

