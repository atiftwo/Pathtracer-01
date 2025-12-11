#include "Program.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Program
{
	GLFWwindow* producedWindow;

	int ProduceWindow()
	{
		if (!glfwInit()) return 1;

		// Window creation primary section
		{
			// Set window size according to screen size
			GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* currentVideoMode = glfwGetVideoMode(currentMonitor);
			int screenWidth = currentVideoMode->width * 14/16;
			int screenHeight = currentVideoMode->height * 6/8;

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_VISIBLE, FALSE);

			producedWindow = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Triangle", NULL, NULL);
		}
		if (!producedWindow) {
			glfwTerminate();
			return 1;
		}

		// Manually load dwmapi to change border colour
		{
			HMODULE dwmapiHandle = LoadLibrary("Dwmapi.dll");

			HWND win32_windowHandle = glfwGetWin32Window(producedWindow);
			int tmp = TRUE;

			auto SetAttribute = (int(*)(HWND, DWORD, LPCVOID, DWORD))GetProcAddress(dwmapiHandle, "DwmSetWindowAttribute");
			SetAttribute(win32_windowHandle, 20, &tmp, sizeof(int));

			FreeLibrary(dwmapiHandle);
		}

		// Setup OpenGL
		glfwMakeContextCurrent(producedWindow);
		{
			auto loadProcFunc = [](const char* name) -> void* {
				return (void*)glfwGetProcAddress(name);
			};
			gladLoadGLLoader(loadProcFunc);
		}
		glfwSwapInterval(1);
		glfwShowWindow(producedWindow);

		return 0;
	}

	int width, height;
	void StartUpdateLoop(void(*UpdateLoopFunction)())
	{
		while (!glfwWindowShouldClose(producedWindow)) {
			glfwGetFramebufferSize(producedWindow, &width, &height);

			glViewport(0, 0, width, height);
        	glClear(GL_COLOR_BUFFER_BIT);

			UpdateLoopFunction();
			
			glfwSwapBuffers(producedWindow);
			glfwPollEvents();
		}
	}

	// Get functions
	glm::ivec2 GetWindowSize()
	{
		return {width, height};
	}

	void Exit()
	{
		glfwTerminate();
	}
}