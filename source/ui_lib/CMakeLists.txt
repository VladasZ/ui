cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ui_lib)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_library(${PROJECT_NAME} ${SOURCE})

link_project(geometry)
link_project(soil)

conan_target_link_libraries(${PROJECT_NAME})
