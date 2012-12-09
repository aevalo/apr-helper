project(apr-helper-library C CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Apr REQUIRED)
find_package(AprUtil REQUIRED)
find_package(PCRE REQUIRED)

include_directories(${APR_INCLUDE_DIR} ${APR_UTIL_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} ${CMAKE_HOME_DIRECTORY}/src)

# We are using statically linked version of APR
add_definitions(-DAPR_DECLARE_STATIC)

set(APR-HELPER_VERSION_MAJOR 0)
set(APR-HELPER_VERSION_MINOR 1)
set(APR-HELPER_VERSION_PATCH 0)
set(APR-HELPER_VERSION ${APR-HELPER_VERSION_MAJOR}.${APR-HELPER_VERSION_MINOR}.${APR-HELPER_VERSION_PATCH})

set(APR-HELPER_PUBLIC_HEADERS   apr_array.hpp apr_status.hpp mem_pool.hpp
                                non_copyable.hpp regex.hpp string.hpp
                                apr_helper_config.hpp apr_helper_init.hpp)

# No private headers at this time
#set(APR-HELPER_PRIVATE_HEADERS  )

set(APR-HELPER_SOURCES apr_array.cpp apr_status.cpp mem_pool.cpp regex.cpp string.cpp apr_helper_init.cpp)

set(APR-HELPER_NEEDED_LIBRARIES ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY})
if(WIN32)
    set(APR-HELPER_NEEDED_LIBRARIES ${APR-HELPER_NEEDED_LIBRARIES} Ws2_32.lib)
endif(WIN32)

if(APR_HELPER_BUILD_SHARED)
    add_definitions(-DAPR_HELPER_SHARED_LIB -DAPR_HELPER_EXPORTING)
    add_library(apr-helper SHARED ${APR-HELPER_PUBLIC_HEADERS} ${APR-HELPER_SOURCES})
else(APR_HELPER_BUILD_SHARED)
    add_library(apr-helper STATIC ${APR-HELPER_PUBLIC_HEADERS} ${APR-HELPER_SOURCES})
endif(APR_HELPER_BUILD_SHARED)

set_target_properties(apr-helper PROPERTIES
                        PUBLIC_HEADER "${APR-HELPER_PUBLIC_HEADERS}"
                          VERSION "${APR-HELPER_VERSION}"
                        SOVERSION "${APR-HELPER_VERSION}")

target_link_libraries(apr-helper ${APR-HELPER_NEEDED_LIBRARIES})

install(TARGETS apr-helper
  RUNTIME DESTINATION bin
  PUBLIC_HEADER DESTINATION include/apr-helper
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib/static)
