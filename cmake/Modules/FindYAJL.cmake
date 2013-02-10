# - Try to find YAJL
# Once done, this will define
#
#  YAJL_FOUND - system has yajl
#  YAJL_INCLUDE_DIRS - the yajl include directories
#  YAJL_LIBRARIES - link these to use yajl

include(FindPackageHandleStandardArgs)

# Include dir
find_path(YAJL_INCLUDE_DIR
  NAMES yajl/yajl_version.h
  HINTS $ENV{YAJLDIR}
  PATH_SUFFIXES include)

# Finally the library itself
if(YAJL_USE_STATIC)
  find_library(YAJL_LIBRARY
    NAMES yajl
    HINTS $ENV{YAJLDIR}
    PATH_SUFFIXES lib64 lib)
else(YAJL_USE_STATIC)
  find_library(YAJL_LIBRARY
    NAMES yajl_s
    HINTS $ENV{YAJLDIR}
    PATH_SUFFIXES lib64 lib)
endif(YAJL_USE_STATIC)

IF(YAJL_INCLUDE_DIR AND YAJL_LIBRARY)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(APR DEFAULT_MSG YAJL_LIBRARY YAJL_INCLUDE_DIR)
  
  # Set the final string here so the GUI reflects the final state.
  SET(YAJL_LIBRARY ${YAJL_LIBRARY} CACHE STRING "Where YAJL library can be found")
  SET(YAJL_INCLUDE_DIR ${YAJL_INCLUDE_DIR} CACHE STRING "Where YAJL headers can be found")
  MARK_AS_ADVANCED(YAJL_LIBRARY YAJL_INCLUDE_DIR)
ENDIF(YAJL_INCLUDE_DIR AND YAJL_LIBRARY)
