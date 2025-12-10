#pragma once

namespace Program
{
	int ProduceWindow();
	void StartUpdateLoop(void(*UpdateLoopFunction)());
}