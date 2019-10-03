# -*- cmake -*-

# - Find G3LOG library
# Find the g3log includes and library
# This module defines
# G3LOG_INCLUDE_DIR, where to find g2log.hpp, etc.
# G3LOG_LIBRARIES, the libraries needed to use libg3logger_shared.so.
# G3LOG_FOUND, If false, do not try to use g3log.

find_path(G3LOG_INCLUDE_DIR
          g3log/g3log.hpp
          /include
          /usr/include
          /usr/local/include
          #${CMAKE_CURRENT_SOURCE_DIR}/submodules/build-g3log/include
          #${CMAKE_CURRENT_SOURCE_DIR}/submodules/g3log/src
          )

find_library(G3LOG_LIBRARIES
             NAMES g3logger
             PATHS /usr
                   /lib
                   /usr/lib
                   /usr/local/lib
                   /usr/local/homebrew/lib
                   /opt/local/lib
                   ~/Library/Frameworks
                   /Library/Frameworks
                   /sw
                   /opt/local
                   /opt/csw
                   /opt
                   #${CMAKE_CURRENT_SOURCE_DIR}/submodules/build-g3log
             )

if(G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)
  set(G3LOG_FOUND "YES")
else(G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)
  set(G3LOG_FOUND "NO")
endif(G3LOG_LIBRARIES AND G3LOG_INCLUDE_DIR)

if(G3LOG_FOUND)
  if(NOT G3LOG_FIND_QUIETLY)
    message(STATUS "Found G3LOG: ${G3LOG_LIBRARIES}")
  endif(NOT G3LOG_FIND_QUIETLY)
else(G3LOG_FOUND)
  if(G3LOG_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find G3LOG library")
  endif(G3LOG_FIND_REQUIRED)
endif(G3LOG_FOUND)
