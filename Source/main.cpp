//#include <iostream>
#include "Program.hpp"
#include <glad/glad.h>

int main()
{
	if (Program::ProduceWindow() != 0) return 1;

	// Shader initialisaiton
	const char* fragmentShaderCode =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	const char* vertexShaderCode =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main() {gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	auto UpdateFunction = []() -> void
	{
		
	};
	Program::StartUpdateLoop(UpdateFunction);

	Program::Deinitialise();
	return 0;
}