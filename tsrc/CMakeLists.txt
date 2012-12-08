project(apr-helper-tests C CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Apr REQUIRED)
find_package(AprUtil REQUIRED)
find_package(PCRE REQUIRED)

add_definitions(-DAPR_DECLARE_STATIC)

if(APR_HELPER_BUILD_SHARED)
    add_definitions(-DAPR_HELPER_SHARED_LIB)
endif(APR_HELPER_BUILD_SHARED)

include_directories(${APR_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} ${CMAKE_HOME_DIRECTORY}/src)

add_executable(dump_ini main.cpp)
target_link_libraries(dump_ini ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY} apr-helper)

install(TARGETS dump_ini RUNTIME DESTINATION bin)
install(FILES test.ini DESTINATION test_data)
