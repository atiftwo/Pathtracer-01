#pragma once

#include <glm/glm.hpp>

namespace Program
{
	int ProduceWindow();
	void StartUpdateLoop(void(*UpdateLoopFunction)());
	void Exit();

	glm::ivec2 GetWindowSize();
}