add_executable(Main WIN32 "Main.cpp")
target_sources(Main PRIVATE "Windows/Setup.cpp")
#target_sources(Main PRIVATE "CPUPathtracer/Main.cpp")

target_sources(Main PRIVATE "${GLAD_SourceDir}/glad.c")
target_include_directories(Main PUBLIC "${GLAD_Include}")

target_link_libraries(Main PUBLIC "${GLFW_Library}")
target_include_directories(Main PUBLIC "${GLFW_Include}")

target_link_libraries(Main PRIVATE "Dwmapi.lib")

target_link_options(Main PUBLIC "-static")
target_compile_options(Main PUBLIC "-static")