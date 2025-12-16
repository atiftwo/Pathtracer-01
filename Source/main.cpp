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

			vert = {cos(angle+curAngle), sin(angle+curAngle), 0.0};
		};

		for (int i = 0; i < 3; ++i)
		RotateVertsFunc(vertices[i], 0.0026*programWindow.GetElapsedTime());

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			// Create a window called "My First Tool", with a menu bar.
			bool my_tool_active = true;
			float my_color[4] = {0.5, 0.5, 0.8, 1.0};
			ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
			if (my_tool_active) {
				if (ImGui::BeginMenuBar())
				{
					if (ImGui::BeginMenu("File"))
					{
						if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
						if (ImGui::MenuItem("Save", "Ctrl+S"))   { /* Do stuff */ }
						if (ImGui::MenuItem("Close", "Ctrl+W"))  { my_tool_active = false; }
						ImGui::EndMenu();
					}
					ImGui::EndMenuBar();
				}

				// Edit a color stored as 4 floats
				ImGui::ColorEdit4("Color", my_color);

				// Generate samples and plot them
				float samples[100];
				for (int n = 0; n < 100; n++)
					samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
				ImGui::PlotLines("Samples", samples, 100);

				// Display contents in a scrolling region
				ImGui::TextColored(ImVec4(1,1,0,1), "Important Stuff");
				ImGui::BeginChild("Scrolling");
				for (int n = 0; n < 50; n++)
					ImGui::Text("%04d: Some text", n);
				ImGui::EndChild();
			}
			ImGui::End();

		ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		programWindow.UpdateWindow();
	}

	return 0;
}