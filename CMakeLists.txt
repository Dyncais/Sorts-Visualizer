cmake_minimum_required(VERSION 3.10)

project(SimpleSort)

add_subdirectory(vendor/raylib)

add_executable(SimpleSort main.cpp)

target_link_libraries(SimpleSort PRIVATE raylib)