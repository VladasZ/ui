cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

setup_exe(ui)

link_project(ui_lib)

link_project_at_path(image     ${image_path}    )
link_project_at_path(geometry  ${geometry_path} )
link_project_at_path(cpp_utils ${cpp_utils_path})
