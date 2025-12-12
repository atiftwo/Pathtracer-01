# Source files

add_executable(Main WIN32 "Main.cpp")
target_sources(Main PRIVATE "Program.cpp")

# Includes and linking

target_sources(Main PRIVATE "${GLAD_SourceDir}/glad.c")
target_include_directories(Main PUBLIC "${GLAD_Include}")

target_link_libraries(Main PUBLIC "${GLFW_Library}")
target_include_directories(Main PUBLIC "${GLFW_Include}")

#target_link_libraries(Main PRIVATE "Dwmapi.lib")
# NOTE: Manually load it and then free it, because it's only used once

target_link_options(Main PUBLIC "-static")
target_compile_options(Main PUBLIC "-static")