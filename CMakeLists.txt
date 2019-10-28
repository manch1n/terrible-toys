cmake_minimum_required (VERSION 3.16)

add_compile_options(-std=c++11)

project(PROJECT_ONE)

add_executable(benchmark benchmark.cc mamutex.cc)

target_link_libraries(benchmark pthread)
