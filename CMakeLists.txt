project(apr-helper C CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

include(EnsureOutOfSourceBuild)

EnsureOutOfSourceBuild("Out-of-source build required.")

add_subdirectory(src)
add_subdirectory(tsrc)

file(GLOB APR_HELPER_CMAKE_MODULES RELATIVE ${CMAKE_SOURCE_DIR} "${CMAKE_SOURCE_DIR}/cmake/Modules/*.cmake")
install(FILES ${APR_HELPER_CMAKE_MODULES} DESTINATION share/apr-helper/cmake/Modules)
