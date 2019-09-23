string (REPLACE ";" " " INPUTS "${INPUTS}")
string (REPLACE ";" " " OUTPUTS "${OUTPUTS}")

message(STATUS "CXTPL_tool_PROGRAM = ${CXTPL_tool_PROGRAM}")
message(STATUS "input_files (for ${CXTPL_tool_PROGRAM}) = ${INPUTS}")
message(STATUS "output_files (for ${CXTPL_tool_PROGRAM}) = ${OUTPUTS}")
execute_process(COMMAND
  ${CXTPL_tool_PROGRAM} --threads ${THREADS} --input_files ${INPUTS} --output_files ${OUTPUTS}
  #${CXTPL_tool_PROGRAM} --threads 4 --input_files /home/avakimov_am/job/CXXCTP/resources/cxtpl/enum_gen_hpp.cxtpl --output_files /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/enum_gen_hpp.cxtpl.cpp
  #${CXTPL_tool_PROGRAM} --threads 4 --input_files /home/avakimov_am/job/CXXCTP/resources/cxtpl/enum_gen_hpp.cxtpl /home/avakimov_am/job/CXXCTP/resources/cxtpl/enum_gen_cpp.cxtpl /home/avakimov_am/job/CXXCTP/resources/cxtpl/typeclass_gen_cpp.cxtpl /home/avakimov_am/job/CXXCTP/resources/cxtpl/typeclass_gen_hpp.cxtpl /home/avakimov_am/job/CXXCTP/resources/cxtpl/typeclass_instance_gen_cpp.cxtpl /home/avakimov_am/job/CXXCTP/resources/cxtpl/typeclass_instance_gen_hpp.cxtpl --output_files /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/enum_gen_hpp.cxtpl.cpp /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/enum_gen_cpp.cxtpl.cpp /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/typeclass_gen_cpp.cxtpl.cpp /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/typeclass_gen_hpp.cxtpl.cpp /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/typeclass_instance_gen_cpp.cxtpl.cpp /home/avakimov_am/job/CXXCTP/resources/cxtpl/generated/typeclass_instance_gen_hpp.cxtpl.cpp
  TIMEOUT 7200 # sec
  RESULT_VARIABLE retcode
  ERROR_VARIABLE _ERROR_VARIABLE
)
if(NOT "${retcode}" STREQUAL "0")
  message( FATAL_ERROR "Bad exit status ${retcode} ${_ERROR_VARIABLE}")
endif()
