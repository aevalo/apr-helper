# Locate apr-util library
# This module defines
# APR_UTIL_LIBRARY, the name of the library to link against
# APR_UTIL_FOUND, if false, do not try to link to apr
# APR_UTIL_INCLUDE_DIR, where to find apr.h

FIND_PATH(APR_UTIL_INCLUDE_DIR apu.h
  HINTS
  $ENV{APRUTILDIR}
  PATH_SUFFIXES include/apr-util include)

FIND_LIBRARY(APR_UTIL_LIBRARY
  NAMES aprutil aprutil-1
  HINTS
  $ENV{APRUTILDIR}
  PATH_SUFFIXES lib64 lib)

IF(APR_UTIL_INCLUDE_DIR AND APR_UTIL_LIBRARY)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(APR_UTIL DEFAULT_MSG APR_UTIL_INCLUDE_DIR APR_UTIL_LIBRARY)
  
  # Set the final string here so the GUI reflects the final state.
  SET(APR_UTIL_LIBRARY ${APR_UTIL_LIBRARY} CACHE STRING "Where the APR-Utility library can be found")
  SET(APR_UTIL_INCLUDE_DIR ${APR_UTIL_INCLUDE_DIR} CACHE STRING "Where the APR-Utility headers can be found")
  MARK_AS_ADVANCED(APR_UTIL_INCLUDE_DIR APR_UTIL_LIBRARY)
ENDIF(APR_UTIL_INCLUDE_DIR AND APR_UTIL_LIBRARY)
