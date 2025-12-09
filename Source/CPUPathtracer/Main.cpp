#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void UpdateTick()
{
	glClearColor((glm::cos(glfwGetTime())+1)*0.5, 0.0, 0.0, 0.0);
}