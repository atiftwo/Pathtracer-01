#include "Program.hpp"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <windows.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// Callback functions' definition
inline glm::ivec2 windowSize;
inline void WindowResizeCallback(GLFWwindow*, int, int);

// Primary functions' implementation
Program::Window::~Window() {
	Deinitialise();
}

GLFWwindow* currentWindow;
int Program::Window::Create() {
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

		currentWindow = glfwCreateWindow(screenWidth, screenHeight, "OpenGL Triangle", NULL, NULL);
	}
	if (!currentWindow) {
		glfwTerminate();
		return 1;
	}

	// Manually load dwmapi to change border colour
	{
		HMODULE dwmapiHandle = LoadLibrary("Dwmapi.dll");

		HWND win32_windowHandle = glfwGetWin32Window(currentWindow);
		int tmp = TRUE;

		auto SetAttribute = (int(*)(HWND, DWORD, LPCVOID, DWORD))GetProcAddress(dwmapiHandle, "DwmSetWindowAttribute");
		SetAttribute(win32_windowHandle, 20, &tmp, sizeof(int));

		FreeLibrary(dwmapiHandle);
	}

	// Set callbacks
	glfwSetFramebufferSizeCallback(currentWindow, WindowResizeCallback);

	// Setup OpenGL
	glfwMakeContextCurrent(currentWindow);
	{
		auto loadProcFunc = [](const char* name) -> void* {
			return (void*)glfwGetProcAddress(name);
		};
		gladLoadGLLoader(loadProcFunc);
	}
	glfwSwapInterval(1);
	IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
	// Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
	style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(currentWindow, true);
	#ifdef __EMSCRIPTEN__
		ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
	#endif
	ImGui_ImplOpenGL3_Init("#version 330 core");
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glfwShowWindow(currentWindow);
	return 0;
}
void Program::Window::Deinitialise() {
	if (GLFWwindow) glfwDestroyWindow(currentWindow);
	glfwTerminate();
}

void Program::Window::UpdateWindow() {
	glfwSwapBuffers(currentWindow);
	glfwPollEvents();
}

// Set functions' implementation

// Get functions' implementation
bool Program::Window::WindowWillClose() {
	return glfwWindowShouldClose(currentWindow);
}
const glm::ivec2& Program::Window::GetWindowSize() {
	return windowSize;
}
double Program::Window::GetElapsedTime() {
	return glfwGetTime();
}

// Callback functions' implementation
inline void WindowResizeCallback(GLFWwindow* window, int width, int height) {
	windowSize.x = width;
	windowSize.y = height;
	glViewport(0, 0, width, height);
}