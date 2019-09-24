# -*- cmake -*-

# - Find RANG library

FIND_PATH(RANG_INCLUDE_DIR rang.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/submodules/rang/include
  /include
  /usr/include
  /usr/local/include
)

IF (RANG_INCLUDE_DIR)
  SET(RANG_FOUND "YES")
ELSE ()
  SET(RANG_FOUND "NO")
ENDIF ()

IF (RANG_FOUND)
  IF (NOT RANG_FIND_QUIETLY)
    MESSAGE(STATUS "Found RANG: ${RANG_INCLUDE_DIR}")
  ENDIF ()
ELSE ()
  IF (RANG_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find RANG library")
  ENDIF ()
ENDIF ()
