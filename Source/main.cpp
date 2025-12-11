//#include <iostream>
#include <GLFW/glfw3.h>
#include "Program.hpp"
#include "Pathtracer/Render.hpp"

int main()
{
	if (Program::ProduceWindow() != 0) return 1;
	Pathtracer::Init();

	auto UpdateFunction = []() -> void {Pathtracer::Render(glfwGetTime());};
	Program::StartUpdateLoop(UpdateFunction);

	Program::Exit();
	return 0;
}