//#include <iostream>
#include <GLFW/glfw3.h>
#include "Program.hpp"

int main()
{
	if (Program::ProduceWindow() != 0) return 1;

	auto UpdateFunction = []() -> void {};
	Program::StartUpdateLoop(UpdateFunction);

	Program::Exit();
	return 0;
}