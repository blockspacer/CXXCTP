set(cxtpl_out_dir ${CMAKE_CURRENT_LIST_DIR}/generated)
set(cxtpl_in_dir ${CMAKE_CURRENT_LIST_DIR}/cxtpl)

list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_gen_cpp.cxtpl")
list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_gen_hpp.cxtpl")

list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_gen_cpp.cxtpl.cpp")
list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_gen_hpp.cxtpl.cpp")

# remove old codegen files
conditional_remove(TRUE ${cxtpl_out_dir} ${CMAKE_CURRENT_SOURCE_DIR})

# create new codegen files
target_add_cxtpl_tool(TARGET CXXCTP_core
                      GUID "typeclass"
                      INPUTS_DIR "${cxtpl_in_dir}"
                      OUTPUTS_DIR "${cxtpl_out_dir}"
                      INPUTS "${cxtpl_inputs}"
                      OUTPUTS "${cxtpl_outputs}")
