# Locate PCRE library
# This module defines
# PCRE_LIBRARY, the name of the library to link against
# PCRE_FOUND, if false, do not try to link to apr
# PCRE_INCLUDE_DIR, where to find apr.h

FIND_PATH(PCRE_INCLUDE_DIR pcre.h
  HINTS
  $ENV{PCREDIR}
  PATH_SUFFIXES include/pcre include)

FIND_LIBRARY(PCRE_LIBRARY
  NAMES pcre
  HINTS
  $ENV{PCREDIR}
  PATH_SUFFIXES lib64 lib)

IF(PCRE_INCLUDE_DIR AND PCRE_LIBRARY)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCRE DEFAULT_MSG PCRE_INCLUDE_DIR PCRE_LIBRARY)
  
  # Set the final string here so the GUI reflects the final state.
  SET(PCRE_LIBRARY ${PCRE_LIBRARY} CACHE STRING "Where the PCRE library can be found")
  SET(PCRE_INCLUDE_DIR ${PCRE_INCLUDE_DIR} CACHE STRING "Where the PCRE headers can be found")
  MARK_AS_ADVANCED(PCRE_INCLUDE_DIR PCRE_LIBRARY)
ENDIF(PCRE_INCLUDE_DIR AND PCRE_LIBRARY)
