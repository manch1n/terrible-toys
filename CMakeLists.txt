cmake_minimum_required (VERSION 3.16)

add_compile_options(-std=c++17)

project(PROJECT_ONE)

add_executable(benchmark benchmark.cc mathreadpool.cc)

target_link_libraries(benchmark pthread)
