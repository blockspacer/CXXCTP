# see https://github.com/feelpp/feelpp/tree/v0.103.1/cmake/modules/FindCling.cmake
# see https://github.com/alandefreitas/find_package_online/blob/master/Modules/FindCling.cmake
# see https://github.com/alandefreitas/find_package_online/blob/master/Modules/ExternalProjectCling.cmake

if(CLING_DIR)
    message(STATUS "[cling] CLING_DIR: ${CLING_DIR}")
endif()

if(CLING_PREFIX)
    message(STATUS "[cling] CLING_PREFIX: ${CLING_PREFIX}")
endif()

find_path(CLING_Interpreter_INCLUDE_DIR ClingOptions.h
    HINTS
    ${CLING_DIR}/src/tools/cling/include/cling/Interpreter
    $ENV{CLING_PREFIX}/include/cling/Interpreter
    ${CLING_PREFIX}/include/cling/Interpreter
    /usr/include/cling/Interpreter
    /usr/local/include/cling/Interpreter
    /opt/local/include/cling/Interpreter
    NO_DEFAULT_PATH
)

include(${CLING_Interpreter_INCLUDE_DIR}/../../../../../../build/lib/cmake/llvm/LLVMConfig.cmake)

if(LLVM_BUILD_BINARY_DIR)
    message(STATUS "[cling] LLVM_BUILD_BINARY_DIR: ${LLVM_BUILD_BINARY_DIR}")
else()
    message(FATAL_ERROR "[cling] LLVM_BUILD_BINARY_DIR not found: ${LLVM_BUILD_BINARY_DIR}")
endif()

list(APPEND CLING_DEFINITIONS LLVMDIR="${LLVM_BUILD_BINARY_DIR}")

list(APPEND CLING_INCLUDE_DIRS ${LLVM_BUILD_BINARY_DIR}/include)
list(APPEND CLING_INCLUDE_DIRS ${CLING_Interpreter_INCLUDE_DIR}/../..)
list(APPEND CLING_INCLUDE_DIRS ${CLING_Interpreter_INCLUDE_DIR}/../../../../../../build/include) # path to "llvm/Config/llvm-config.h"
list(APPEND CLING_INCLUDE_DIRS ${CLING_Interpreter_INCLUDE_DIR}/../../../../../../src/include) # path to "llvm/ADT/StringRef.h"
list(APPEND CLING_INCLUDE_DIRS ${CLING_Interpreter_INCLUDE_DIR}/../../../../../../src/tools/clang/include/) # path to "clang/Lex/HeaderSearchOptions.h"
list(APPEND CLING_INCLUDE_DIRS ${CLING_Interpreter_INCLUDE_DIR}/../../../../../../build/tools/clang/include/) # path to "clang/Basic/DiagnosticCommonKinds.inc"

set(LIBRARY_SEARCH_PATHS
  ${CLING_DIR}/build/lib/
  $ENV{CLING_PREFIX}/lib
  ${CLING_PREFIX}/lib
  /usr/lib
  /usr/local/lib
  /opt/local/lib
  NO_DEFAULT_PATH
)

find_library(CLING_LIBRARIES cling
    HINTS ${LIBRARY_SEARCH_PATHS}
)

find_library(CLING_clingInterpreter_LIBRARIES clingInterpreter
    HINTS ${LIBRARY_SEARCH_PATHS}
)

if(NOT TARGET Cling::ClingInterpreter)
  add_library(Cling::ClingInterpreter UNKNOWN IMPORTED)
  set_target_properties(Cling::ClingInterpreter PROPERTIES
    IMPORTED_LOCATION "${CLING_clingInterpreter_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${CLING_INCLUDE_DIRS}"
    INTERFACE_COMPILE_DEFINITIONS "${CLING_DEFINITIONS}"
  )
endif()

find_library(CLING_clingMetaProcessor_LIBRARIES clingMetaProcessor
    HINTS ${LIBRARY_SEARCH_PATHS}
)

if(NOT TARGET Cling::clingMetaProcessor)
  add_library(Cling::clingMetaProcessor UNKNOWN IMPORTED)
  set_target_properties(Cling::clingMetaProcessor PROPERTIES
    IMPORTED_LOCATION "${CLING_clingMetaProcessor_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${CLING_INCLUDE_DIRS}"
    INTERFACE_COMPILE_DEFINITIONS "${CLING_DEFINITIONS}"
  )
endif()

find_library(CLING_clingUtils_LIBRARIES clingUtils
    HINTS ${LIBRARY_SEARCH_PATHS}
)

if(NOT TARGET Cling::clingUtils)
  add_library(Cling::clingUtils UNKNOWN IMPORTED)
  set_target_properties(Cling::clingUtils PROPERTIES
    IMPORTED_LOCATION "${CLING_clingUtils_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${CLING_INCLUDE_DIRS}"
    INTERFACE_COMPILE_DEFINITIONS "${CLING_DEFINITIONS}"
  )
endif()

find_program(CLING_BIN cling
    HINTS
    ${CLING_DIR}/build/bin/
    ${CLING_PREFIX}/bin
    /usr/bin
    /usr/local/bin
    $PATH
    CMAKE_SYSTEM_PROGRAM_PATH
)

if(NOT TARGET Cling::Cling)
  add_library(Cling::Cling UNKNOWN IMPORTED)
  set_target_properties(Cling::Cling PROPERTIES
    IMPORTED_LOCATION "${CLING_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${CLING_INCLUDE_DIRS}"
    INTERFACE_COMPILE_DEFINITIONS "${CLING_DEFINITIONS}"
  )
endif()

message( STATUS "[cling] include dir: ${CLING_INCLUDE_DIRS}" )
message( STATUS "[cling] libraries: ${CLING_LIBRARIES}" )
message( STATUS "[cling] binary: ${CLING_BIN}" )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS( Cling REQUIRED_VARS CLING_BIN )
