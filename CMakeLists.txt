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

set(APR-HELPER_VERSION_MAJOR 0)
set(APR-HELPER_VERSION_MINOR 1)
set(APR-HELPER_VERSION_PATCH 0)
set(APR-HELPER_VERSION ${APR-HELPER_VERSION_MAJOR}.${APR-HELPER_VERSION_MINOR}.${APR-HELPER_VERSION_PATCH})

set(APR-HELPER_PUBLIC_HEADERS   src/apr_array.hpp src/apr_status.hpp
                                src/mem_pool.hpp src/non_copyable.hpp
                                src/regex.hpp src/string.hpp)

# No private headers at this time
#set(APR-HELPER_PRIVATE_HEADERS  )

set(APR-HELPER_SOURCES          src/apr_array.cpp src/apr_status.cpp
                                src/mem_pool.cpp src/regex.cpp src/string.cpp)

set(APR-HELPER_NEEDED_LIBRARIES ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY})
if(WIN32)
    set(APR-HELPER_NEEDED_LIBRARIES ${APR-HELPER_NEEDED_LIBRARIES} Ws2_32.lib)
endif(WIN32)

add_library(apr-helper SHARED ${APR-HELPER_PUBLIC_HEADERS} ${APR-HELPER_SOURCES})

set_target_properties(apr-helper PROPERTIES
                        PUBLIC_HEADER APR-HELPER_PUBLIC_HEADERS
                        VERSION APR-HELPER_VERSION
                        SOVERSION APR-HELPER_VERSION)

target_link_libraries(apr-helper ${APR-HELPER_NEEDED_LIBRARIES})

add_executable(dump_ini tsrc/main.cpp)
target_link_libraries(dump_ini apr-helper)
