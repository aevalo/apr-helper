project(apr-helper C CXX)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake/Modules
)

include(EnsureOutOfSourceBuild)

EnsureOutOfSourceBuild("Out-of-source build required.")

find_package(Apr REQUIRED)
find_package(AprUtil REQUIRED)
find_package(PCRE REQUIRED)

include_directories(${APR_INCLUDE_DIR} ${APR_UTIL_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} src)

# We are using statically linked version of APR
add_definitions(-DAPR_DECLARE_STATIC)

add_library(apr-helper STATIC src/string.cpp src/regex.cpp src/mem_pool.cpp src/apr_status.cpp src/apr_array.cpp)
if(WIN32)
    target_link_libraries(apr-helper ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY} Ws2_32.lib)
else(WIN32)
    target_link_libraries(apr-helper ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY})
endif(WIN32)

add_executable(dump_ini tsrc/main.cpp)
if(WIN32)
    target_link_libraries(dump_ini ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY} apr-helper Ws2_32.lib)
else(WIN32)
    target_link_libraries(dump_ini ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY} apr-helper)
endif(WIN32)
