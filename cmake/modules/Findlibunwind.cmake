# Find the libunwind library
#
#  LIBUNWIND_FOUND       - True if libunwind was found.
#  LIBUNWIND_LIBRARIES   - The libraries needed to use libunwind
#  LIBUNWIND_INCLUDE_DIR - Location of unwind.h and libunwind.h

#  INPUT: LIBUNWIND_ROOT - path where include + lib of libunwind installation is located

find_path(LIBUNWIND_INCLUDE_DIR libunwind.h
          HINTS /usr/ /usr/local/
          PATH_SUFFIXES include
          PATHS "${LIBUNWIND_ROOT}/include")

find_library(LIBUNWIND_GENERIC_LIBRARY libunwind.a unwind
             HINTS /usr/ /usr/local/
             PATH_SUFFIXES lib
             PATHS "${LIBUNWIND_ROOT}/lib")

if(LIBUNWIND_INCLUDE_DIR)
  # nothing
  if(LIBUNWIND_GENERIC_LIBRARY)
    set(LIBUNWIND_LIBRARIES ${LIBUNWIND_GENERIC_LIBRARY})

    # For some reason, we have to link to two libunwind shared object files:
    # one arch-specific and one not.
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
      set(LIBUNWIND_ARCH "arm")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64"
           OR CMAKE_SYSTEM_PROCESSOR STREQUAL "amd64")
      set(LIBUNWIND_ARCH "x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^i.86$")
      set(LIBUNWIND_ARCH "x86")
    endif()

    if(LIBUNWIND_ARCH)
      find_library(LIBUNWIND_SPECIFIC_LIBRARY libunwind-${LIBUNWIND_ARCH}.a
                   "unwind-${LIBUNWIND_ARCH}"
                   HINTS /usr/
                   PATH_SUFFIXES lib
                   PATHS "${LIBUNWIND_ROOT}")
      if(NOT LIBUNWIND_SPECIFIC_LIBRARY)
        message(FATAL_ERROR "failed to find unwind-${LIBUNWIND_ARCH}")
      endif()
      set(LIBUNWIND_LIBRARIES ${LIBUNWIND_LIBRARIES} ${LIBUNWIND_SPECIFIC_LIBRARY})
    endif(LIBUNWIND_ARCH)

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libunwind DEFAULT_MSG LIBUNWIND_INCLUDE_DIR)

    mark_as_advanced(LIBUNWIND_LIBRARIES LIBUNWIND_INCLUDE_DIR)

  else(LIBUNWIND_GENERIC_LIBRARY)
    message("-- Could NOT find Libunwind ")
  endif(LIBUNWIND_GENERIC_LIBRARY)
else(LIBUNWIND_INCLUDE_DIR)
  message("-- Could NOT find libunwind.h")
endif(LIBUNWIND_INCLUDE_DIR)
