cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ui)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})

link_project(ui_lib)
