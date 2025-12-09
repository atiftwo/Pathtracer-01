cmake_minimum_required(VERSION 4.2)

project("Pathtracer-01")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include("DefineBuildType")

# Includes & etc.
include_directories("${GLM_Include}")
#include_directories("${VulkanSDK_Root}/Include")
#link_directories("${VulkanSDK_Root}/Lib")

add_subdirectory("Source")