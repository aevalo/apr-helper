project(apr-helper-tests C CXX)
cmake_minimum_required(VERSION 2.8)

find_package(Apr REQUIRED)
find_package(AprUtil REQUIRED)
find_package(PCRE REQUIRED)

add_definitions(-DAPR_DECLARE_STATIC)

# For exampe g++ needs this.
# Visual Studio 2010 apparently does not.
if(APR_HELPER_BUILD_HAS_CXX11)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -std=c++11")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -std=c++11")
endif(APR_HELPER_BUILD_HAS_CXX11)

if(APR_HELPER_BUILD_SHARED)
  add_definitions(-DAPR_HELPER_SHARED_LIB)
endif(APR_HELPER_BUILD_SHARED)

include_directories(${APR_INCLUDE_DIR} ${PCRE_INCLUDE_DIR} ${CMAKE_HOME_DIRECTORY}/src)

add_executable(dump_ini main.cpp)
target_link_libraries(dump_ini ${APR_LIBRARY} ${APR_UTIL_LIBRARY} ${PCRE_LIBRARY} apr-helper)

add_executable(checksummer checksummer.cpp)
target_link_libraries(checksummer ${APR_LIBRARY} ${APR_UTIL_LIBRARY})

add_executable(gen_random gen_random.cpp)
target_link_libraries(gen_random ${APR_LIBRARY} ${APR_UTIL_LIBRARY})

install(TARGETS dump_ini RUNTIME DESTINATION bin)
install(FILES test.ini test.json 2048Bytes.bin Hello.txt DESTINATION share/apr-helper/test_data)

