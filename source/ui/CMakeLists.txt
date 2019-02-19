cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(ui)

add_catalog_recursive(${PROJECT_SOURCE_DIR} /source SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})

link_project(ui_lib)

link_project_at_path(SOIL      ${soil_path}     )
link_project_at_path(image     ${image_path}    )
link_project_at_path(geometry  ${geometry_path} )
link_project_at_path(cpp_utils ${cpp_utils_path})

conan_target_link_libraries(${PROJECT_NAME})
