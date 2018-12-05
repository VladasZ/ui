cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

include(utils/utils.cmake)

set(CMAKE_CXX_STANDARD 17)

project(ui)

add_subdirectory(source/ui)
add_subdirectory(source/ui_lib)
add_subdirectory(source/geometry)

