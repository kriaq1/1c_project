cmake_minimum_required(VERSION 3.16)
project(1c_project)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(read_image)
add_subdirectory(solution)

add_executable(1c_project main.cpp main.h)

target_link_libraries(1c_project ReadImageLibrary SolutionLibrary)