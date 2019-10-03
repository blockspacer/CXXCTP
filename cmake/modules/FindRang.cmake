# -*- cmake -*-

# - Find RANG library

find_path(RANG_INCLUDE_DIR
          rang.hpp
          ${CMAKE_CURRENT_SOURCE_DIR}/submodules/rang/include
          /include
          /usr/include
          /usr/local/include)

if(RANG_INCLUDE_DIR)
  set(RANG_FOUND "YES")
else()
  set(RANG_FOUND "NO")
endif()

if(RANG_FOUND)
  if(NOT RANG_FIND_QUIETLY)
    message(STATUS "Found RANG: ${RANG_INCLUDE_DIR}")
  endif()
else()
  if(RANG_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find RANG library")
  endif()
endif()
