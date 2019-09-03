#------------------------------------------------------------------------------
# CLING - the C++ LLVM-based InterpreterG :)
#
# This file is dual-licensed: you can choose to license it under the University
# of Illinois Open Source License or the GNU Lesser General Public License. See
# LICENSE.TXT for details.
#------------------------------------------------------------------------------

cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

# Building as separate project.
project(CXXCTP)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc++abi")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -lc++abi")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -lc++abi")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -lc++abi")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -stdlib=libc++")
#
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--no-undefined")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-undefined")
#
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--as-needed")
#set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,--as-needed")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--as-needed")

set(CLING_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cling-build/" CACHE STRING "CLING DIR")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
# TODO
list(APPEND CMAKE_MODULE_PATH ${JINJA2CPP_INSTALL_DIR}/lib/jinja2cpp)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Jinja2Cpp/cmake/public)

# Keep symbols for JIT resolution
set(LLVM_NO_DEAD_STRIP 1)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

include( Dependencies.cmake )

# TODO
#find_package(jinja2cpp)
find_package(Jinja2Cpp)

# NOTE: disable CLING by default,
# so you can see sources in IDE and use tab-complete
set(ENABLE_CLING TRUE CACHE BOOL "ENABLE_CLING")

if(ENABLE_CLING)
  list(APPEND CLING_DEFINITIONS CLING_IS_ON=1)
  # The project has one binary:
  add_executable(CXXCTP
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_cling.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/someEnum.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/someEnum.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/type_erasure2.cpp
  )
else(ENABLE_CLING)
  message(FATAL_ERROR "Only Cling interpreter is supported for now")
  # The project has one binary:
  #add_executable(CXXCTP
  #  src/app_loop.cpp
  #  src/http_callbacks.cpp
  #  src/mime_type.cpp
  #)
endif(ENABLE_CLING)

set( USED_SYSTEM_LIBS
  Cling::Cling
  Cling::ClingInterpreter
  Cling::clingUtils
  Cling::clingMetaProcessor
  Threads::Threads # pthread, https://cmake.org/cmake/help/v3.13/module/FindThreads.html
  #${X11_LIBRARIES} # https://cmake.org/cmake/help/v3.13/module/FindX11.html
  #${CMAKE_DL_LIBS} # https://cmake.org/cmake/help/v3.13/variable/CMAKE_DL_LIBS.html
  #EXPAT::EXPAT # https://cmake.org/cmake/help/v3.13/module/FindEXPAT.html
  #ZLIB::ZLIB # https://cmake.org/cmake/help/v3.13/module/FindZLIB.html
  # Custom libs
  stdc++fs # C++17 std::filesystem
  CACHE INTERNAL "USED_SYSTEM_LIBS" )

set( USED_BOOST_LIBS
  Boost::boost
  Boost::atomic
  Boost::chrono
  Boost::date_time
  Boost::filesystem
  Boost::graph
  Boost::log
  Boost::program_options
  Boost::regex
  Boost::system
  Boost::thread
  CACHE INTERNAL "USED_BOOST_LIBS" )

# ...which links against clingInterpreter (and its dependencies).
target_link_libraries(CXXCTP
  # TODO: use FindClang.cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangARCMigrate.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangAnalysis.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangAST.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangASTMatchers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangBasic.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangCodeGen.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangDriver.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangDynamicASTMatchers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangEdit.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFormat.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFrontendTool.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangIndex.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangLex.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangParse.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangRewrite.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangRewriteFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangSema.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangSerialization.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerCheckers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerCore.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangTooling.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangToolingCore.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangToolingRefactor.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerCore.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangDynamicASTMatchers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangCodeGen.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFrontendTool.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclang.so
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangEdit.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangRewriteFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangDriver.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangSema.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangASTMatchers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangSerialization.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangBasic.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangAST.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangTooling.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFormat.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangToolingRefactor.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangLex.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangFrontend.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangRewrite.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangToolingCore.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangIndex.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangAnalysis.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangParse.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangStaticAnalyzerCheckers.a
  ${CMAKE_CURRENT_SOURCE_DIR}/cling-build/build/lib/libclangARCMigrate.a
  # system libs
  ${USED_SYSTEM_LIBS}
  # boost libs
  ${USED_BOOST_LIBS}
  #
  #${JINJA2CPP_LIBRARY}
  /usr/local/lib/static/libjinja2cpp.a
)

target_compile_definitions( CXXCTP PUBLIC
  ${CLING_DEFINITIONS}
  # https://stackoverflow.com/a/30877725
  BOOST_SYSTEM_NO_DEPRECATED
  BOOST_ERROR_CODE_HEADER_ONLY
  # https://jinja2cpp.dev/docs/build_and_install.html#dependency-management-modes
  variant_CONFIG_SELECT_VARIANT=variant_VARIANT_NONSTD
)

target_include_directories( CXXCTP PUBLIC
  ${JINJA2CPP_INCLUDE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/submodules/Jinja2Cpp/thirdparty/nonstd/expected-light/include/
)

set_target_properties(CXXCTP
  PROPERTIES ENABLE_EXPORTS 1)

if(MSVC)
  set_target_properties(CXXCTP PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
  set_property(TARGET CXXCTP APPEND_STRING PROPERTY LINK_FLAGS
              "/EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00D_K@Z
               /EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00DM@Z
               /EXPORT:cling_runtime_internal_throwIfInvalidPointer")
endif()
