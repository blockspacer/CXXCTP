# Finds liblz4.
#
# This module defines:
# LZ4_FOUND
# LZ4_INCLUDE_DIR
# LZ4_LIBRARY
#

find_path(LZ4_INCLUDE_DIR NAMES lz4.h)

find_library(LZ4_LIBRARY_DEBUG NAMES lz4d)
find_library(LZ4_LIBRARY_RELEASE NAMES lz4)

include(SelectLibraryConfigurations)
select_library_configurations(LZ4)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LZ4 DEFAULT_MSG LZ4_LIBRARY LZ4_INCLUDE_DIR)

if(LZ4_FOUND)
  message(STATUS "Found LZ4: ${LZ4_LIBRARY}")
endif()

mark_as_advanced(LZ4_INCLUDE_DIR LZ4_LIBRARY)
