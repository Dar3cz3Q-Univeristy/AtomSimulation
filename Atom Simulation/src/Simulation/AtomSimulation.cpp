#include "AtomSimulation.h"

AtomSimulation::AtomSimulation()
{
	m_Window = new Window(800, 800, "Symulacja atomu");
}

AtomSimulation::~AtomSimulation()
{
	if (!m_Window)
		delete m_Window;
}

void AtomSimulation::Run()
{
	m_Window->Run();
}
