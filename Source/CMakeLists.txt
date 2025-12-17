# Source files
add_executable(Main WIN32 "Main.cpp")
target_sources(Main PRIVATE "Program.cpp")

# Includes and linking

# GLM
set(GLM_IncludeDir "" CACHE PATH "GLM include directory")
include_directories("${GLM_IncludeDir}")

# GLAD
set(GLAD_IncludeDir "" CACHE PATH "GLAD include directory")
target_include_directories(Main PUBLIC "${GLAD_IncludeDir}")

set(GLAD_SourceDir "" CACHE PATH "Directory with the GLAD source file")
target_sources(Main PUBLIC "${GLAD_SourceDir}/glad.c")

# GLFW
set(GLFW_IncludeDir "" CACHE PATH "GLFW include directory")
target_include_directories(Main PUBLIC "${GLFW_IncludeDir}")

set(GLFW_LibraryPath "" CACHE FILEPATH "Path to a compiled GLFW 3 library")
target_link_libraries(Main PUBLIC "${GLFW_LibraryPath}")

# ImGui
set(ImGui_RootDir "" CACHE FILEPATH "Root ImGui directory")
target_include_directories(Main PUBLIC "${ImGui_RootDir}")

file(GLOB ImGui_Sources "${ImGui_RootDir}/*.cpp")
target_sources(Main PUBLIC "${ImGui_Sources}")

target_sources(Main PUBLIC "${ImGui_RootDir}/backends/imgui_impl_opengl3.cpp")
target_sources(Main PUBLIC "${ImGui_RootDir}/backends/imgui_impl_glfw.cpp")

#target_link_libraries(Main PRIVATE "Dwmapi.lib")
# NOTE: Manually load it and then free it, because it's only used once

target_link_options(Main PUBLIC "-static")
target_compile_options(Main PUBLIC "-static")