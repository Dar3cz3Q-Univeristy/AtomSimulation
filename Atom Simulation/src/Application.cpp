#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

#define width 800
#define height 800

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit()) {
		std::cout << "Warning: Initializing glfw failed!" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "Atom Simulation", NULL, NULL);

	if (!window) {
		glfwTerminate();
		std::cout << "Warning: Creating window failed!" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	gladLoadGL();

	std::cout << glGetString(GL_VERSION) << std::endl;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}