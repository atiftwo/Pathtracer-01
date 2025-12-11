#include <glad/glad.h>
#include <glm/glm.hpp>

#include <GLFW/glfw3.h>
#include "../Program.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace Program
{

	typedef struct Vertex
	{
		glm::vec2 pos;
		glm::vec3 col;
	} Vertex;

	static const Vertex vertices[3] =
	{
		{ { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
		{ {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
		{ {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
	};

	static const char* vertex_shader_text =
	"#version 330\n"
	"uniform mat4 MVP;\n"
	"in vec3 vCol;\n"
	"in vec2 vPos;\n"
	"out vec3 color;\n"
	"void main()\n"
	"{\n"
	"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
	"    color = vCol;\n"
	"}\n";

	static const char* fragment_shader_text =
	"#version 330\n"
	"in vec3 color;\n"
	"out vec4 fragment;\n"
	"void main()\n"
	"{\n"
	"    fragment = vec4(color, 1.0);\n"
	"}\n";

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

		// TODO: Manually load dwmapi
		{
			enum DWMWINDOWATTRIBUTE {
				DWMWA_NCRENDERING_ENABLED,
				DWMWA_NCRENDERING_POLICY,
				DWMWA_TRANSITIONS_FORCEDISABLED,
				DWMWA_ALLOW_NCPAINT,
				DWMWA_CAPTION_BUTTON_BOUNDS,
				DWMWA_NONCLIENT_RTL_LAYOUT,
				DWMWA_FORCE_ICONIC_REPRESENTATION,
				DWMWA_FLIP3D_POLICY,
				DWMWA_EXTENDED_FRAME_BOUNDS,
				DWMWA_HAS_ICONIC_BITMAP,
				DWMWA_DISALLOW_PEEK,
				DWMWA_EXCLUDED_FROM_PEEK,
				DWMWA_CLOAK,
				DWMWA_CLOAKED,
				DWMWA_FREEZE_REPRESENTATION,
				DWMWA_PASSIVE_UPDATE_MODE,
				DWMWA_USE_HOSTBACKDROPBRUSH,
				DWMWA_USE_IMMERSIVE_DARK_MODE = 20,
				DWMWA_WINDOW_CORNER_PREFERENCE = 33,
				DWMWA_BORDER_COLOR,
				DWMWA_CAPTION_COLOR,
				DWMWA_TEXT_COLOR,
				DWMWA_VISIBLE_FRAME_BORDER_THICKNESS,
				DWMWA_SYSTEMBACKDROP_TYPE,
				DWMWA_LAST
			};
			HMODULE dwmapiHandle = LoadLibrary("Dwmapi.dll");

			HWND win32_windowHandle = glfwGetWin32Window(producedWindow);
			int tmp = TRUE;

			auto SetAttribute = (int(*)(HWND, DWORD, LPCVOID, DWORD))GetProcAddress(dwmapiHandle, "DwmSetWindowAttribute");
			SetAttribute(win32_windowHandle, DWMWA_USE_IMMERSIVE_DARK_MODE, &tmp, sizeof(int));

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

	void StartUpdateLoop(void(*UpdateLoopFunction)())
	{
		while (!glfwWindowShouldClose(producedWindow)) {
			int width, height;
			glfwGetFramebufferSize(producedWindow, &width, &height);

			glViewport(0, 0, width, height);
        	glClear(GL_COLOR_BUFFER_BIT);

			UpdateLoopFunction();

			glfwSwapBuffers(producedWindow);
			glfwPollEvents();
		}
	}

	void Exit()
	{
		glfwTerminate();
	}
}