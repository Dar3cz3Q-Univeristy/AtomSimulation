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
#include "Camera.h"

#define AS_DELTA_TIME 1.0/30.0

class Window
{
public:
	Window() = default;
	Window(int width, int height, const std::string& title);
	~Window();

	void Run();
private:
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	std::string m_Title;
	bool m_Running;
	bool m_Minimized;
	float m_LastFrameTime;
	LayerStack m_LayerStack;
	unsigned int m_Counter;
	Camera m_Camera;
	Renderer m_Renderer;

	void Init();
	void Update();
	void Events();
	void PushLayer(Layer* layer);
	void Statistics();
};

void WindowResizeCallBack(GLFWwindow* window, int width, int height);

