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

# The project has one binary:
add_executable(CXXCTP_tool
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_native.cpp
)

target_link_libraries(CXXCTP_tool PUBLIC
  CXXCTP_core
)

target_link_libraries( CXXCTP_tool PRIVATE
  ${base_LIB}
  ${build_util_LIB}
  CONAN_PKG::corrade
  Corrade::PluginManager
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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/includes/version.hpp.in
  ${PROJECT_BINARY_DIR}/version.hpp)

set_source_files_properties(${PROJECT_BINARY_DIR}/version.hpp
  PROPERTIES GENERATED 1)

install(TARGETS CXXCTP_tool DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
