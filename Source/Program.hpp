#pragma once

#include <glm/glm.hpp>

namespace Program {
	class Window {
		Window();
		~Window();

		public:
		int Create();
		void StartUpdateLoop();
		void BreakUpdateLoop();
		void Deinitialise();

		typedef void(*UpdateLoopFunction)();
		UpdateLoopFunction updateLoopFunction;

		glm::ivec2 GetWindowSize();
		double GetElapsedTime();
	};
}