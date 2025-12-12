#pragma once
#include <glm/glm.hpp>

namespace Program {
	class Window {
		public:
		~Window();

		int Create();
		void StartUpdateLoop();
		void BreakUpdateLoop();
		void Deinitialise();

		void UpdateWindow();
		bool WindowWillClose();

		const glm::ivec2& GetWindowSize();
		double GetElapsedTime();
	};
}