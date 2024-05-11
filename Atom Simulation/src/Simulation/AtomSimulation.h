#pragma once
#include "Window.h"

class AtomSimulation {
public:
	AtomSimulation();
	~AtomSimulation();
	void Run();
private:
	Window* m_Window;
};
