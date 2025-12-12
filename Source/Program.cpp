#include "Program.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// Callbacks
void WindowResizeCallback(GLFWwindow*, int, int);

GLFWwindow* producedWindow;

int Program::ProduceWindow()
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

	// Set callbacks
	glfwSetFramebufferSizeCallback(producedWindow, WindowResizeCallback);

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

// Get functions
int width, height;
glm::ivec2 Program::GetWindowSize() {
	return {width, height};
}
double Program::GetElapsedTime() {
	return glfwGetTime();
}

void Program::Deinitialise() {
	glfwTerminate();
}

void Program::StartUpdateLoop(void(*UpdateLoopFunction)())
{
	while (!glfwWindowShouldClose(producedWindow)) {
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		UpdateLoopFunction();
		
		glfwSwapBuffers(producedWindow);
		glfwPollEvents();
	}
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	width = width;
	glViewport(0, 0, width, height);
}

