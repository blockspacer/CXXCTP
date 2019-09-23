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

# Keep symbols for JIT resolution
set(LLVM_NO_DEAD_STRIP 1)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

include( Dependencies.cmake )

# NOTE: disable CLING by default,
# so you can see sources in IDE and use tab-complete
set(ENABLE_CLING FALSE CACHE BOOL "ENABLE_CLING")

set(ENABLE_CXXCTP TRUE CACHE BOOL "ENABLE_CXXCTP")

list(APPEND COMMON_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/clangUtils.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/clangUtils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/funcParser.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/funcParser.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/someEnum.hpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/someEnum.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/type_erasure_my_interface.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/type_erasure_my_interface2.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/type_erasure_my_interface_my_interface2.cpp
  #${CMAKE_CURRENT_SOURCE_DIR}/src/types_for_erasure.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DispatchQueue.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DispatchQueue.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/clangPipeline.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/clangPipeline.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ClingInterpreterModule.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/ClingInterpreterModule.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/inputThread.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/inputThread.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflectionCache.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflectionCache.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflTypes.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflTypes.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/TypeInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/TypeInfo.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflectAST.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ReflectAST.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/reflect/ast_utils.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/template_engine/CXTPL_AnyDict.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/template_engine/CXTPL_AnyDict.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/template_engine/I_Dict.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/template_engine/I_Dict.cpp
)

include(Codegen_files.cmake)

if(ENABLE_CLING)
  #add_library(simple_lib SHARED #STATIC
  #  ${CMAKE_CURRENT_SOURCE_DIR}/src/simplelib.cpp
  #)

  list(APPEND CLING_DEFINITIONS CLING_IS_ON=1)
  if(ENABLE_CXXCTP)
    add_executable(CXXCTP
     ${COMMON_FILES}
     ${CMAKE_CURRENT_SOURCE_DIR}/src/main_cling.cpp
     # TODO: DEPENDS ${cxtpl_outputs}
    )
  endif(ENABLE_CXXCTP)
else(ENABLE_CLING)
  #message(FATAL_ERROR "Only Cling interpreter is supported for now")
  if(ENABLE_CXXCTP)
    add_executable(CXXCTP
     ${COMMON_FILES}
     ${CMAKE_CURRENT_SOURCE_DIR}/src/main_cling.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/ctp_scripts/app_loop.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/ctp_scripts/app_loop.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/ctp_scripts/ctp_registry.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/ctp_scripts/ctp_registry.hpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/cxtpl/CXTPL_STD.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/resources/cxtpl/CXTPL_STD.hpp
    )
  endif(ENABLE_CXXCTP)
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

list(APPEND CLING_LIBS
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
)

# ...which links against clingInterpreter (and its dependencies).
if(ENABLE_CXXCTP)
  target_link_libraries(CXXCTP
    #simple_lib
    ${CLING_LIBS}
    # system libs
    ${USED_SYSTEM_LIBS}
    # boost libs
    ${USED_BOOST_LIBS}
  )
endif(ENABLE_CXXCTP)

if(ENABLE_CXXCTP)
  target_compile_definitions( CXXCTP PUBLIC
    ${CLING_DEFINITIONS}
    # https://stackoverflow.com/a/30877725
    BOOST_SYSTEM_NO_DEPRECATED
    BOOST_ERROR_CODE_HEADER_ONLY
    IS_CXXCTP=1
  )
endif(ENABLE_CXXCTP)

macro(conditional_remove ARG_DO_REMOVE ARG_DIR ARG_WORKING_DIR)
  if(${ARG_DO_REMOVE})
    if (NOT EXISTS ${ARG_DIR})
      message(STATUS "not existent: ${ARG_DIR}" --yellow --bold)
    endif (NOT EXISTS ${ARG_DIR})

    if(IS_DIRECTORY ${ARG_DIR})
      execute_process(
        COMMAND ${CMAKE_COMMAND} "-E" "remove_directory" "${ARG_DIR}"
        WORKING_DIRECTORY ${ARG_WORKING_DIR}
        TIMEOUT 7200 # sec
      )
      message(STATUS "removed old directory ${ARG_DIR}" --yellow --bold)
      if (EXISTS ${ARG_DIR})
        message(STATUS "can`t remove directory ${ARG_DIR}" --red --bold)
      endif(EXISTS ${ARG_DIR})
    else(IS_DIRECTORY ${ARG_DIR})
      execute_process(
        COMMAND ${CMAKE_COMMAND} "-E" "remove" "${ARG_DIR}"
        WORKING_DIRECTORY ${ARG_WORKING_DIR}
        TIMEOUT 7200 # sec
      )
      message(STATUS "removed old file ${ARG_DIR}" --yellow --bold)
      if (EXISTS ${ARG_DIR})
        message(STATUS "can`t remove file ${ARG_DIR}" --red --bold)
      endif(EXISTS ${ARG_DIR})
    endif(IS_DIRECTORY ${ARG_DIR})
  else(${ARG_DO_REMOVE})
    message(STATUS "kept old path: ${ARG_DIR}" --yellow --bold)
  endif(${ARG_DO_REMOVE})
endmacro(conditional_remove)

#target_include_directories( CXXCTP PUBLIC
#)

if(ENABLE_CXXCTP)
  set_target_properties(CXXCTP
    PROPERTIES ENABLE_EXPORTS 1)
endif(ENABLE_CXXCTP)

if(MSVC)
 if(ENABLE_CXXCTP)
   set_target_properties(CXXCTP PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
   set_property(TARGET CXXCTP APPEND_STRING PROPERTY LINK_FLAGS
               "/EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00D_K@Z
                /EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00DM@Z
                /EXPORT:cling_runtime_internal_throwIfInvalidPointer")
  endif(ENABLE_CXXCTP)
endif()

# remove old codegen files
conditional_remove(TRUE ${cxtpl_out_dir} ${CMAKE_CURRENT_SOURCE_DIR})

# create new codegen files
target_add_CXTPL_tool(CXXCTP "${cxtpl_inputs}" "${cxtpl_outputs}")
