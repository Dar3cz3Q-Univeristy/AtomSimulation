#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Debug.h"
#include "Renderer.h"
#include "Shader.h"
#include "Layer.h"
#include "LayerStack.h"

//#define AS_DELTA_TIME 1.0/30.0

class Window
{
public:
	Window() = default;
	Window(uint32_t width, uint32_t height, const std::string& title);
	~Window();
	void Run();
	void Update();
	void Events();
	void PushLayer(Layer* layer);
private:
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	bool m_Running;
	bool m_Minimized;
	float m_LastFrameTime;
	LayerStack m_LayerStack;
};

