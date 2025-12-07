cmake_minimum_required(VERSION 4.2)

project("Pathtracer-01")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include_directories("${VulkanSDKInclude}")
link_directories("${VulkanSDKLib}")
link_directories("${WindowsSDKLib}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include("DefineBuildType")

add_subdirectory("Source")