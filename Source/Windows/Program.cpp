#include <GLFW/glfw3.h>
#include "../Program.hpp"

namespace Program
{
	GLFWwindow* producedWindow;

	int ProduceWindow()
	{
		if (!glfwInit()) return 1;

		// Window creation primary section
		{
			// Divide screen w, h both by 16 and subtract 2 and then multiply by 16
			GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* currentVideoMode = glfwGetVideoMode(currentMonitor);
			int screenWidth = (currentVideoMode->width/16 - 2) * 16;
			int screenHeight = (currentVideoMode->height/8 - 2) * 8;

			producedWindow = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Triangle", NULL, NULL);
		}
		if (!producedWindow) {
			glfwTerminate();
			return 1;
		}

		glfwMakeContextCurrent(producedWindow);
		glfwSwapInterval(1);

		return 0;
	}

	void StartUpdateLoop(void(*UpdateLoopFunction)())
	{
		while (!glfwWindowShouldClose(producedWindow)) {
			UpdateLoopFunction();
		}
	}
}