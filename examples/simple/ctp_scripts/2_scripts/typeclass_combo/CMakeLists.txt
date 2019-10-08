#message(FATAL_ERROR CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR})

set(cxtpl_out_dir ${CMAKE_CURRENT_LIST_DIR}/generated)
set(cxtpl_in_dir ${CMAKE_CURRENT_LIST_DIR}/cxtpl)

list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_combo_gen_cpp.cxtpl")
list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_combo_gen_hpp.cxtpl")

list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_combo_gen_cpp.cxtpl.cpp")
list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_combo_gen_hpp.cxtpl.cpp")

# remove old codegen files
conditional_remove(TRUE ${cxtpl_out_dir} ${CMAKE_CURRENT_SOURCE_DIR})

# create new codegen files
target_add_cxtpl_tool(CXXCTP_core "typeclass_combo" "${cxtpl_in_dir}" "${cxtpl_out_dir}" "${cxtpl_inputs}" "${cxtpl_outputs}")
