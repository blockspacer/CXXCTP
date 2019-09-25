cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

set(PROJECT_NAME CXXCTP_tool)
set(PROJECT_VERSION 1.0.1)

# Building as separate project.
project(${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  LANGUAGES CXX)

# Keep symbols for JIT resolution
set(LLVM_NO_DEAD_STRIP 1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

set( BOOST_ROOT CACHE STRING /usr )
set( Boost_ADDITIONAL_VERSIONS "1.62 1.63 1.64 1.65 1.66 1.67 1.68 1.69" )
set( BOOST_LIBS CACHE STRING ${BOOST_ROOT}/lib )
find_package( Boost
  COMPONENTS program_options filesystem regex date_time system thread graph log
  EXACT REQUIRED )

find_package( Threads REQUIRED )
message(STATUS "CMAKE_THREAD_LIBS_INIT = ${CMAKE_THREAD_LIBS_INIT}")

find_package( X11 REQUIRED )
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

find_package( EXPAT REQUIRED )
message(STATUS "EXPAT_LIBRARIES = ${EXPAT_LIBRARIES}")

find_package( ZLIB REQUIRED )
message(STATUS "ZLIB_LIBRARIES = ${ZLIB_LIBRARIES}")

message(STATUS "CMAKE_DL_LIBS = ${CMAKE_DL_LIBS}")

# The project has one binary:
add_executable(CXXCTP_tool
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_native.cpp
)

target_link_libraries(CXXCTP_tool PUBLIC
  ${FOLLY_LIBRARIES}
  CXXCTP_core
  # system libs
  Threads::Threads # pthread, https://cmake.org/cmake/help/v3.13/module/FindThreads.html
  ${X11_LIBRARIES} # https://cmake.org/cmake/help/v3.13/module/FindX11.html
  ${CMAKE_DL_LIBS} # https://cmake.org/cmake/help/v3.13/variable/CMAKE_DL_LIBS.html
  EXPAT::EXPAT # https://cmake.org/cmake/help/v3.13/module/FindEXPAT.html
  ZLIB::ZLIB # https://cmake.org/cmake/help/v3.13/module/FindZLIB.html
  # Custom libs
  stdc++fs # C++17 std::filesystem
  # boost libs
  ${USED_BOOST_LIBS}
  boost_outcome
  microsoft_gsl
  double-conversion
  # CXXCTP
  # @note: Order matters https://stackoverflow.com/a/10269201/10904212
  ${LIBIBERTY_LIBRARY} # used by folly
  ${LIBEVENT_LIB} # used by folly
  ${LZ4_LIBRARY} # used by folly
  ${LIBGFLAGS_LIBRARY} # used by folly
  ${G3LOG_LIBRARIES} # used by folly
  glog
  gflags
)

# NOTE: don`t link twice to clang or you will get
# `LLVM ERROR: inconsistency in registered CommandLine options`
#target_link_libraries(CXXCTP_tool PRIVATE
#  ${CLING_LIBS}
#  Cling::Cling
#  Cling::ClingInterpreter
#  Cling::clingUtils
#  Cling::clingMetaProcessor
#)

target_compile_options(CXXCTP_tool PRIVATE
  -frtti)

target_compile_definitions(CXXCTP_tool PUBLIC
  ${CLING_DEFINITIONS}
)

set_target_properties(CXXCTP_tool
  PROPERTIES ENABLE_EXPORTS 1)

# POSITION_INDEPENDENT_CODE for -fPIC
set_property(TARGET CXXCTP_tool PROPERTY POSITION_INDEPENDENT_CODE ON)

if(ENABLE_CLING)
  if(MSVC)
   set_target_properties(CXXCTP_tool PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
   set_property(TARGET CXXCTP_tool APPEND_STRING PROPERTY LINK_FLAGS
               "/EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00D_K@Z
                /EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00DM@Z
                /EXPORT:cling_runtime_internal_throwIfInvalidPointer")
  endif()
endif(ENABLE_CLING)

target_include_directories(CXXCTP_tool PUBLIC
  ${PROJECT_BINARY_DIR} # path to version.hpp
)

set(PDOLLAR "$") # Hack for nested vars in configure_file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/includes/version.hpp.in
  ${PROJECT_BINARY_DIR}/version.hpp)

set_source_files_properties(${PROJECT_BINARY_DIR}/version.hpp
  PROPERTIES GENERATED 1)

install(TARGETS CXXCTP_tool DESTINATION bin)
