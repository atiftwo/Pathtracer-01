add_executable(main WIN32 "main.cpp")
#target_sources(main PRIVATE "Render.cpp")

target_sources(main PRIVATE "${GLAD_SourceDir}/glad.c")
target_include_directories(main PUBLIC "${GLAD_Include}")

target_link_libraries(main PUBLIC "${GLFW_Library}")
target_include_directories(main PUBLIC "${GLFW_Include}")

target_compile_options(main PUBLIC "-static")