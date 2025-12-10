//#include <iostream>
#include <GLFW/glfw3.h>
#include "Program.hpp"

int main()
{
	if (!Program::ProduceWindow()) return 1;

	auto UpdateFunction = []() -> void {
		glfwPollEvents();
	};
	Program::StartUpdateLoop(UpdateFunction);

	glfwTerminate();
	return 0;
}