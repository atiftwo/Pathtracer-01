#include "Render.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "../Program.hpp"

namespace Pathtracer
{
	unsigned int shaderProgram;
	GLuint vertexBufferArray;

	float vertexBuffer[] = {
			0.0, 0.5, 0.0,
			0.5, 0.0, 0.0,
			-0.5, 0.0, 0.0
	};

	void Init()
	{
		unsigned int vertexBufferObject;
		glGenBuffers(1, &vertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), &vertexBuffer, GL_DYNAMIC_DRAW);

		static const char* fragmentShaderCode =
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

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// This will identify our vertex buffer
		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &vertexBufferArray);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferArray);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferArray), &vertexBufferArray, GL_STATIC_DRAW);

	}
	void Render()
	{
		
	}
}