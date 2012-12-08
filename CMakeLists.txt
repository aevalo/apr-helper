project(apr-helper C CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

include(EnsureOutOfSourceBuild)

EnsureOutOfSourceBuild("Out-of-source build required.")

add_subdirectory(src)
add_subdirectory(tsrc)
