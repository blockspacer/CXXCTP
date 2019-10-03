# https://github.com/bro/cmake/blob/master/FindJeMalloc.cmake
# - Try to find google test headers and libraries.
#
# Usage of this module as follows:
#
#     find_package(Folly)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  FOLLY_ROOT_DIR Set this variable to the root installation of
#                    folly if the module has problems finding
#                    the proper installation path.
#
# Variables defined by this module:
#
#  FOLLY_FOUND             System has folly libs/headers
#  FOLLY_LIBRARIES         The folly library/libraries
#  FOLLY_INCLUDE_DIR       The location of folly headers

find_path(FOLLY_ROOT_DIR NAMES include/folly/folly-config.h)

find_library(FOLLY_LIBRARIES
             NAMES folly
             HINTS ENV LD_LIBRARY_PATH ENV DYLD_LIBRARY_PATH
             PATHS ${FOLLY_ROOT_DIR}/lib
                   /usr
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
                   /opt)

find_library(FOLLY_BENCHMARK_LIBRARIES
             NAMES follybenchmark
             HINTS ENV LD_LIBRARY_PATH ENV DYLD_LIBRARY_PATH
             PATHS ${FOLLY_ROOT_DIR}/lib
                   /usr
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
                   /opt)

find_library(FOLLY_DC_LIBRARY
             NAMES double-conversion
             HINTS ENV LD_LIBRARY_PATH ENV DYLD_LIBRARY_PATH
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
                   /opt)

find_path(FOLLY_INCLUDE_DIR NAMES folly/folly-config.h HINTS ${FOLLY_ROOT_DIR}/include)

find_library(FOLLY_INCLUDE_DIR
             NAMES folly/folly-config.h
             HINTS ENV LD_LIBRARY_PATH ENV DYLD_LIBRARY_PATH
             PATHS ${FOLLY_ROOT_DIR}/include
                   /usr/include
                   /usr/local/include
                   /usr/local/homebrew/include
                   /opt/local/include)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Folly DEFAULT_MSG FOLLY_LIBRARIES FOLLY_INCLUDE_DIR)

mark_as_advanced(FOLLY_ROOT_DIR
                 FOLLY_LIBRARIES
                 FOLLY_DC_LIBRARY
                 FOLLY_BENCHMARK_LIBRARIES
                 FOLLY_INCLUDE_DIR)
