string(REPLACE ";" " " INPUTS "${INPUTS}")

message(STATUS "CXXCTP_tool_PROGRAM = ${CXXCTP_tool_PROGRAM}")
message(STATUS "EXTRA_ARGS = ${EXTRA_ARGS}")
message(STATUS "sources path (for ${CXXCTP_tool_PROGRAM}) = ${SRCDIR}")
message(STATUS "input_files (for ${CXXCTP_tool_PROGRAM}) = ${INPUTS}")
message(STATUS "output dir (for ${CXXCTP_tool_PROGRAM}) = ${OUTDIR}")
message(
  STATUS "CXXCTP_tool_LOG_CONFIG (for ${CXXCTP_tool_PROGRAM}) = ${CXXCTP_tool_LOG_CONFIG}"
  )

if(CXXCTP_tool_CLEAN)
  if(EXISTS ${OUTDIR})
    file(REMOVE_RECURSE ${OUTDIR})
  endif(EXISTS ${OUTDIR})
endif(CXXCTP_tool_CLEAN)

separate_arguments(EXTRA_ARGS)
separate_arguments(INPUTS)

execute_process(
  COMMAND ${CXXCTP_tool_PROGRAM}
          -L
          "${CXXCTP_tool_LOG_CONFIG}"
          --ctp_scripts_paths=${SRCDIR}
          --srcdir=${SRCDIR}
          --resdir=${OUTDIR}
          ${EXTRA_ARGS}
          #-extra-arg=-I~/job/CXXCTP/include
          #-extra-arg=-I~/job/CXXCTP/cling-build/build/lib/clang/5.0.0/include
          #-extra-arg=-I~/job/CXXCTP/cling-build/src/include/
          #-extra-arg=-I~/job/CXXCTP/cling-build/build/include/
          #-extra-arg=-I~/job/CXXCTP/cling-build/src/tools/clang/include/
          #-extra-arg=-I~/job/CXXCTP/cling-build/build/tools/clang/include/
          #-extra-arg=-I~/job/CXXCTP/cling-build/src/tools/cling/include/
          ${INPUTS}
          #~/job/CXXCTP/examples/simple/src/for_codegen/test.cpp
          #~/job/CXXCTP/examples/simple/src/for_codegen/ReflShapeKind.hpp
          #~/job/CXXCTP/examples/simple/src/for_codegen/test_typeclass_base1.hpp
          #~/job/CXXCTP/examples/simple/src/for_codegen/test_typeclass_instance1.hpp
          #~/job/CXXCTP/examples/simple/src/for_codegen/test_typeclass_combo1.hpp
          #TIMEOUT 7200 # sec
  RESULT_VARIABLE retcode
  ERROR_VARIABLE _ERROR_VARIABLE)
if(NOT "${retcode}" STREQUAL "0")
  message(FATAL_ERROR "Bad exit status ${retcode} ${_ERROR_VARIABLE}")
endif()
