#pragma once

#include "Window.h"
#include "Specification.h"

class AtomSimulation 
{
public:
	AtomSimulation();
	~AtomSimulation();
	void Run();
private:
	Window* m_Window;
};
