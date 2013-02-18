project(myhello CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Lua51 REQUIRED)

include_directories(${LUA_INCLUDE_DIR})

add_library(myhello SHARED src/libmain.cpp)
target_link_libraries(myhello ${LUA_LIBRARIES})

add_library(libfoo SHARED src/libfoo.cpp)
target_link_libraries(libfoo ${LUA_LIBRARIES})

set_target_properties(myhello libfoo PROPERTIES PREFIX "")

install(TARGETS myhello libfoo DESTINATION lib)
