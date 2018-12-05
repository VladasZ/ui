cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(console_drawer)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_library(${PROJECT_NAME} ${SOURCE})

link_project(geometry)
link_project(ui_lib)
