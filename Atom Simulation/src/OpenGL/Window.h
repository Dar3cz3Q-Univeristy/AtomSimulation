#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Debug.h"
#include "Tools.h"

#include "Renderer.h"
#include "Shader.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Camera.h"

#include "AntiAliasing.h"
#include "PostProcessing.h"

#define AS_DELTA_TIME 1.0/30.0

class Window
{
public:
	Window() = default;
	Window(int width, int height, const std::string& title);
	~Window();

	void Run();

	static float GetDeltaTime() { return s_DeltaTime; };
private:
	GLFWwindow* m_Window;
	int m_Width;
	int m_Height;
	std::string m_Title;
	bool m_Running;
	bool m_Minimized;
	LayerStack m_LayerStack;
	unsigned int m_Counter;
	Camera m_Camera;
	Renderer m_Renderer;

	AntiAliasing* m_AntiAliasing;
	PostProcessing* m_PostProcessing;

	static float s_LastFrameTime;
	static float s_DeltaTime;
	static float s_SumDeltaTime;

	void Init();
	void Update();
	void Events();
	void PushLayer(Layer* layer);
	void Statistics();
};

void WindowResizeCallBack(GLFWwindow* window, int width, int height);
void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);