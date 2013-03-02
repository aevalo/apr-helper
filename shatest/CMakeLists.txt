cmake_minimum_required(VERSION 2.8)
project(Stuffs CXX)

find_package(PkgConfig REQUIRED)
pkg_search_module(APR REQUIRED apr-1)
pkg_search_module(APR_UTIL REQUIRED apr-util-1)

set(Python_ADDITIONAL_VERSIONS 2.7)
find_package(PythonLibs REQUIRED)

include_directories(${APR_INCLUDE_DIRS} ${APR_UTIL_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS} src/)
link_directories(${APR_LIBRARY_DIRS} ${APR_UTIL_LIBRARY_DIRS})

add_executable(shatest src/shatest.cpp)
target_link_libraries(shatest ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES})
add_executable(shortopts src/shortopts.cpp)
target_link_libraries(shortopts ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES})
add_executable(longopts src/longopts.cpp)
target_link_libraries(longopts ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES})
add_library(sha1_checksum SHARED src/sha1_checksum.cpp)
target_link_libraries(sha1_checksum ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES})


PYTHON_ADD_MODULE(spam src/spammodule.cpp src/sha1_checksum.cpp)
target_link_libraries(spam ${PYTHON_LIBRARIES} ${APR_LIBRARIES} ${APR_UTIL_LIBRARIES})

PYTHON_ADD_MODULE(sha1 src/python/src/sha1module.cpp)
target_link_libraries(sha1 ${PYTHON_LIBRARIES} sha1_checksum)

add_dependencies(spam shatest shortopts longopts)
add_dependencies(sha1 sha1_checksum)

string(REPLACE "-D" "" STUFFS_OTHER_CFLAGS "${APR_CFLAGS_OTHER};${APR_UTIL_CFLAGS_OTHER}")
string(REPLACE "-" "" STUFFS_OTHER_CFLAGS "${STUFFS_OTHER_CFLAGS};${APR_UTIL_CFLAGS_OTHER}")
set_target_properties(shatest shortopts longopts PROPERTIES
	COMPILE_DEFINITIONS "${STUFFS_OTHER_CFLAGS}")
set_target_properties(spam PROPERTIES VERSION "0.0.1" SOVERSION "0.0.1")
set_target_properties(sha1 PROPERTIES VERSION "0.0.1" SOVERSION "0.0.1")
set_target_properties(sha1_checksum PROPERTIES VERSION "0.0.1" SOVERSION "0.0.1")

install(TARGETS shatest shortopts longopts spam RUNTIME DESTINATION bin LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
