//#include <iostream>
#include "Program.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

int main()
{
	Program::Window programWindow;
	if (programWindow.Create() != 0) return 1;
	
	// Vertex	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glm::vec3 vertices[] = {
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f}
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float rotationSpeed = 0.25;
	while (!programWindow.WindowWillClose()) {
		//glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Rotate verts
		auto RotateVertsFunc = [](glm::vec3& vert, float angle) {
			float dst = sqrt(vert.x*vert.x + vert.y*vert.y);
			float curAngle = atan(abs(vert.y/vert.x));

			// Determine quadrant
			if (vert.x > 0) {if (vert.y < 0) curAngle = 2*3.14159 - curAngle;} // 4th quadrant
			else {
				if (vert.y < 0) curAngle += 3.14159; // 3rd quadrant
				else curAngle = 3.14159 - curAngle;
			}

			vert = {dst*cos(angle+curAngle), dst*sin(angle+curAngle), 0.0};
		};

		for (int i = 0; i < 3; ++i)
		RotateVertsFunc(vertices[i], rotationSpeed);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

			if (ImGui::Begin("My First Tool")) {
				ImGui::SliderFloat("Rotation Speed", &rotationSpeed, -3.14159, 3.14159);
			}
			ImGui::End();

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		programWindow.UpdateWindow();
	}

	return 0;
}