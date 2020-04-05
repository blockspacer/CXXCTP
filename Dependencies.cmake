# Copyright (c) 2019 Denis Trofimov (den.a.trofimov@yandex.ru)
# Distributed under the MIT License.
# See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT

find_package( Threads REQUIRED )
message(STATUS "CMAKE_THREAD_LIBS_INIT = ${CMAKE_THREAD_LIBS_INIT}")

# This project needs cling.
if(ENABLE_CLING)
    find_package(Cling REQUIRED)
endif(ENABLE_CLING)
find_package(CXTPL_tool REQUIRED)

#
# If you have built boost statically you will need to set the Boost_USE_STATIC_LIBS CMake variable to ON
# also don`t forget to set DBOOST_LOG_DYN_LINK https://stackoverflow.com/a/17868918/10904212
# set( Boost_USE_STATIC_LIBS FALSE )
# set( Boost_USE_STATIC_RUNTIME FALSE )
# set( Boost_USE_MULTITHREADED TRUE )
#set( BOOST_ROOT CACHE STRING /usr )
#set( Boost_ADDITIONAL_VERSIONS "1.62 1.63 1.64 1.65 1.66 1.67 1.68 1.69" )
#set( BOOST_LIBS CACHE STRING ${BOOST_ROOT}/lib )
# set( Boost_COMPILER "-gcc" )

#find_package( Boost
#  COMPONENTS
#  coroutine
#  fiber
#  context
#  filesystem
#  program_options
#  regex
#  system
#  thread
#  REQUIRED )

#message("Found Boost ${Boost_LIBRARY_DIRS} ${Boost_LIB_VERSION}")

#if(Boost_VERSION GREATER_EQUAL 107100)
#  add_definitions(-DBOOST_BEAST_SEPARATE_COMPILATION -DBOOST_ASIO_SEPARATE_COMPILATION)
#endif()

find_package( Boost 1.71.0
  COMPONENTS program_options filesystem regex date_time system thread graph
  EXACT REQUIRED )
if(NOT TARGET CONAN_PKG::boost)
  message(FATAL_ERROR "Use boost from conan")
endif()
message(STATUS "Boost_LIBRARIES=${Boost_LIBRARIES}")
message(STATUS "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")

if(NOT TARGET CONAN_PKG::clang_folly_conan)
  message(FATAL_ERROR "Use clang_folly_conan from conan")
endif()

if(NOT TARGET CONAN_PKG::chromium_base)
  message(FATAL_ERROR "Use chromium_base from conan")
endif()

if(NOT TARGET CONAN_PKG::chromium_build_util)
  message(FATAL_ERROR "Use chromium_build_util from conan")
endif()

find_package(chromium_build_util REQUIRED)
#
if(TARGET chromium_build_util::chromium_build_util-static)
  set(build_util_LIB "chromium_build_util::chromium_build_util-static")
else()
  message(FATAL_ERROR "not supported: using system provided chromium_build_util library")
endif()

find_package(chromium_base REQUIRED)
if(TARGET chromium_base::chromium_base-static)
  set(base_LIB chromium_base::chromium_base-static)
else()
  message(FATAL_ERROR "not supported: using system provided chromium_base library")
endif()

set(WITH_TESTSUITE OFF CACHE BOOL "" FORCE) # disable what you don't use
#add_subdirectory(corrade EXCLUDE_FROM_ALL) # so only things you use are built
# see https://doc.magnum.graphics/corrade/corrade-cmake.html#corrade-cmake-subproject
find_package(Corrade REQUIRED PluginManager)

if(NOT TARGET CONAN_PKG::corrade)
  message(FATAL_ERROR "Use corrade from conan")
endif()

add_library( boost_outcome INTERFACE )
target_include_directories( boost_outcome SYSTEM INTERFACE "submodules/boost.outcome/include" )
get_target_property (BOOST_OUTCOME_IMPORTED_LOCATION boost_outcome INTERFACE_INCLUDE_DIRECTORIES)
message( STATUS "boost_outcome=${BOOST_OUTCOME_IMPORTED_LOCATION}" )

add_library(microsoft_gsl INTERFACE)
target_include_directories(microsoft_gsl SYSTEM INTERFACE "submodules/GSL/include")
get_target_property (microsoft_gsl_IMPORTED_LOCATION microsoft_gsl INTERFACE_INCLUDE_DIRECTORIES)
message( STATUS "microsoft_gsl=${microsoft_gsl_IMPORTED_LOCATION}" )

#if(USE_FOLLY)
#  #find_package( Folly REQUIRED )
#  #message( STATUS "FOLLY_LIBRARIES=${FOLLY_LIBRARIES}")
#  #message( STATUS "FOLLY_INCLUDE_DIR=${FOLLY_INCLUDE_DIR}")
#
#  find_package(Libiberty REQUIRED) # used by folly
#  #get_target_property (Libiberty_LOCATION Libiberty INTERFACE_INCLUDE_DIRECTORIES)
#  message( STATUS "LIBIBERTY_INCLUDE_DIR=${LIBIBERTY_INCLUDE_DIR}")
#  message( STATUS "LIBIBERTY_LIBRARY=${LIBIBERTY_LIBRARY}")
#endif()

find_package( X11 REQUIRED )
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

find_package( EXPAT REQUIRED )
message(STATUS "EXPAT_LIBRARIES = ${EXPAT_LIBRARIES}")

find_package( ZLIB REQUIRED )
message(STATUS "ZLIB_LIBRARIES = ${ZLIB_LIBRARIES}")

message(STATUS "CMAKE_DL_LIBS = ${CMAKE_DL_LIBS}")

if(USE_RANG)
  set(RANG_FIND_REQUIRED
    TRUE CACHE BOOL
    "RANG_FIND_REQUIRED")
  find_package(Rang REQUIRED)
  message(STATUS "RANG found at ${RANG_INCLUDE_DIR}")
else()
  message(WARNING "RANG turned off!")
endif()

#find_package(libunwind REQUIRED)
#message(STATUS "LIBUNWIND_LIBRARIES=${LIBUNWIND_LIBRARIES}")
#message(STATUS "LIBUNWIND_INCLUDE_DIR=${LIBUNWIND_INCLUDE_DIR}")
#
#find_package(LibLZMA REQUIRED)
#message(STATUS "LIBLZMA_INCLUDE_DIRS=${LIBLZMA_INCLUDE_DIRS}")
#message(STATUS "LIBLZMA_LIBRARIES=${LIBLZMA_LIBRARIES}")

#if(USE_G3LOG)
#  set(G3LOG_FIND_REQUIRED
#    TRUE CACHE BOOL
#    "G3LOG_FIND_REQUIRED")
#  find_package(g3log REQUIRED)
#  message(STATUS "g3log logger found at ${G3LOG_LIBRARIES} AND ${G3LOG_INCLUDE_DIR}")
#else()
#  message(WARNING "g3log logger turned off!")
#endif()

#find_package(Gflags REQUIRED)
#message(STATUS "LIBGFLAGS_LIBRARY=${LIBGFLAGS_LIBRARY}")
#message(STATUS "LIBGFLAGS_INCLUDE_DIR=${LIBGFLAGS_INCLUDE_DIR}")

#find_package(LZ4 REQUIRED)
#message(STATUS "LZ4_LIBRARY_RELEASE=${LZ4_LIBRARY_RELEASE}")
#message(STATUS "LZ4_INCLUDE_DIR=${LZ4_INCLUDE_DIR}")
#
#find_package(DoubleConversion MODULE REQUIRED)
#message(STATUS "LIBLZMA_INCLUDE_DIRS=${DOUBLE_CONVERSION_LIBRARY}")
#message(STATUS "LIBLZMA_LIBRARIES=${DOUBLE_CONVERSION_INCLUDE_DIR}")

#find_package(LibEvent REQUIRED)
#message(STATUS "LZ4_LIBRARY=${LZ4_LIBRARY}")
#message(STATUS "LZ4_LIBRARY_DEBUG=${LZ4_LIBRARY_DEBUG}")
