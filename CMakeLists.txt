#------------------------------------------------------------------------------
# CLING - the C++ LLVM-based InterpreterG :)
#
# This file is dual-licensed: you can choose to license it under the University
# of Illinois Open Source License or the GNU Lesser General Public License. See
# LICENSE.TXT for details.
#------------------------------------------------------------------------------

cmake_minimum_required( VERSION 3.13.3 FATAL_ERROR )

# Building as separate project.
project(cling-demo)

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
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include( Dependencies.cmake )

set(ENABLE_WEBRTC FALSE CACHE BOOL "ENABLE_WEBRTC")

# NOTE: disable CLING by default,
# so you can see sources in IDE and use tab-complete
set(ENABLE_CLING FALSE CACHE BOOL "ENABLE_CLING")

if(ENABLE_WEBRTC)
  macro(add_webrtc)
    if (WEBRTC_SRC_PATH)
    else()
      message(FATAL_ERROR "WEBRTC_SRC_PATH not set")
      # NOTE: change WEBRTC_SRC_PATH
      # TODO: >>>>>>>>>
      #set(WEBRTC_SRC_PATH "/home/denis/workspace/webrtc-checkout/src")
    endif()
    if (WEBRTC_TARGET_PATH)
    else()
      message(WARNING "using default WEBRTC_TARGET_PATH")
      set(WEBRTC_TARGET_PATH "out/release")
    endif()
    message("WEBRTC_SRC_PATH=${WEBRTC_SRC_PATH}")
    message("WEBRTC_TARGET_PATH=${WEBRTC_TARGET_PATH}")
    if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin"
      OR ${CMAKE_SYSTEM_NAME} MATCHES "Linux"
      OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "^arm")

      set(WEBRTC_DEFINITIONS "-DWEBRTC_POSIX" CACHE INTERNAL "" FORCE)
      set(WEBRTC_LIBRARIES webrtc_full
        webrtc
        rtc_p2p
        jingle_peerconnection_api
        #boringssl
        CACHE INTERNAL "" FORCE)
      set(WEBRTC_LIB_PATHS ${WEBRTC_SRC_PATH}/${WEBRTC_TARGET_PATH}
        ${WEBRTC_SRC_PATH}/${WEBRTC_TARGET_PATH}/obj
        ${WEBRTC_SRC_PATH}/${WEBRTC_TARGET_PATH}/obj/p2p
        ${WEBRTC_SRC_PATH}/${WEBRTC_TARGET_PATH}/obj/api
        #${WEBRTC_SRC_PATH}/${WEBRTC_TARGET_PATH}/obj/third_party/boringssl
        CACHE INTERNAL "" FORCE)
    else()
    # TODO
    # #define WEBRTC_ANDROID 1
    # #define WEBRTC_IOS 1
    # #define WEBRTC_LINUX 1
    # #define WEBRTC_MAC 1
    # #define WEBRTC_WIN 1
    #
    # #define WEBRTC_POSIX 1
    message(FATAL_ERROR "System ${CMAKE_SYSTEM_NAME} not supported")
    endif()
  endmacro(add_webrtc)

  # TODO https://github.com/shakandrew/AgarPlusPlus/blob/abbd548ab1d0e0d908778baa9366fc3a83182f88/CMake/FindWebRTC.cmake
  set(WEBRTC_SRC_PATH CACHE STRING "WEBRTC_SRC_PATH_HERE")
  set(WEBRTC_TARGET_PATH CACHE STRING "WEBRTC_TARGET_PATH_HERE")
  add_webrtc() # from Utils.cmake
endif(ENABLE_WEBRTC)

if(ENABLE_CLING)
  list(APPEND CLING_DEFINITIONS CLING_IS_ON=1)
  # The project has one binary:
  add_executable(cling-demo
    src/main_cling.cpp
  )
else(ENABLE_CLING)
  # The project has one binary:
  add_executable(cling-demo
    src/app_loop.cpp
    src/http_callbacks.cpp
    src/mime_type.cpp
  )
endif(ENABLE_CLING)

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

set( USED_SYSTEM_LIBS
  Cling::Cling
  Cling::ClingInterpreter
  Cling::clingUtils
  Cling::clingMetaProcessor
  Threads::Threads # pthread, https://cmake.org/cmake/help/v3.13/module/FindThreads.html
  ${X11_LIBRARIES} # https://cmake.org/cmake/help/v3.13/module/FindX11.html
  ${CMAKE_DL_LIBS} # https://cmake.org/cmake/help/v3.13/variable/CMAKE_DL_LIBS.html
  EXPAT::EXPAT # https://cmake.org/cmake/help/v3.13/module/FindEXPAT.html
  ZLIB::ZLIB # https://cmake.org/cmake/help/v3.13/module/FindZLIB.html
  # Custom libs
  stdc++fs # C++17 std::filesystem
  CACHE INTERNAL "USED_SYSTEM_LIBS" )

set( USED_3DPARTY_LIBS
  # boost libs
  ${USED_BOOST_LIBS}
  ${WEBRTC_LIBRARIES} # NOTE: place wrtc libs before system libs to prefer wrtc libs
  CACHE INTERNAL "USED_3DPARTY_LIBS" )

# ...which links against clingInterpreter (and its dependencies).
target_link_libraries(cling-demo
  #stdc++ # libstdc++
  #/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++.a
  #/usr/lib/gcc/x86_64-linux-gnu/7/libstdc++fs.a
  #/usr/lib/gcc/x86_64-linux-gnu/8/libstdc++.a
  #/usr/lib/gcc/x86_64-linux-gnu/8/libstdc++fs.a
  # 3dparty libs
  ${USED_3DPARTY_LIBS}
  # system libs
  ${USED_SYSTEM_LIBS}
)

target_compile_definitions( cling-demo PUBLIC
  ${WEBRTC_DEFINITIONS}
  ${CLING_DEFINITIONS}
)

target_link_directories( cling-demo PUBLIC ${WEBRTC_LIB_PATHS} )

set_target_properties(cling-demo
  PROPERTIES ENABLE_EXPORTS 1)

if(MSVC)
  set_target_properties(cling-demo PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS 1)
  set_property(TARGET cling-demo APPEND_STRING PROPERTY LINK_FLAGS
              "/EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00D_K@Z
               /EXPORT:?setValueNoAlloc@internal@runtime@cling@@YAXPEAX00DM@Z
               /EXPORT:cling_runtime_internal_throwIfInvalidPointer")
endif()
