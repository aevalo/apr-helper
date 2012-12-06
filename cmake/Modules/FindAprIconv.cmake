# Locate apr-iconv library
# This module defines
# APR_ICONV_LIBRARY, the name of the library to link against
# APR_ICONV_FOUND, if false, do not try to link to apr
# APR_ICONV_INCLUDE_DIR, where to find apr.h

FIND_PATH(APR_ICONV_INCLUDE_DIR apr_iconv.h
  HINTS
  $ENV{APRICONVDIR}
  PATH_SUFFIXES include/apr-iconv include)

FIND_LIBRARY(APR_ICONV_LIBRARY
  NAMES apriconv apriconv-1
  HINTS
  $ENV{APRDIR}
  PATH_SUFFIXES lib64 lib)

IF(APR_ICONV_INCLUDE_DIR AND APR_ICONV_LIBRARY)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(APR_ICONV DEFAULT_MSG APR_ICONV_INCLUDE_DIR APR_ICONV_LIBRARY)
  
  # Set the final string here so the GUI reflects the final state.
  SET(APR_ICONV_LIBRARY ${APR_ICONV_LIBRARY} CACHE STRING "Where the APR-iconv substitute iconv library can be found")
  SET(APR_ICONV_INCLUDE_DIR ${APR_ICONV_INCLUDE_DIR} CACHE STRING "Where the APR-iconv substitute iconv headers can be found")
  MARK_AS_ADVANCED(APR_ICONV_INCLUDE_DIR APR_ICONV_LIBRARY)
ENDIF(APR_ICONV_INCLUDE_DIR AND APR_ICONV_LIBRARY)
