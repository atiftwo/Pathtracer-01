cmake_minimum_required(VERSION 4.2)

project("Pathtracer-01")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include("Settings")
include("DefineBuildType")

# Includes & etc.
include_directories("${GLM_Include}")

add_subdirectory("Source")