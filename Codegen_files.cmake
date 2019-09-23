set(cxtpl_in_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources/cxtpl")
set(cxtpl_out_dir "${CMAKE_CURRENT_SOURCE_DIR}/resources/cxtpl/generated")

list(APPEND cxtpl_inputs "${cxtpl_in_dir}/enum_gen_hpp.cxtpl")
list(APPEND cxtpl_inputs "${cxtpl_in_dir}/enum_gen_cpp.cxtpl")

list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_gen_cpp.cxtpl")
list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_gen_hpp.cxtpl")

list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_instance_gen_cpp.cxtpl")
list(APPEND cxtpl_inputs "${cxtpl_in_dir}/typeclass_instance_gen_hpp.cxtpl")

list(APPEND cxtpl_outputs "${cxtpl_out_dir}/enum_gen_hpp.cxtpl.cpp")
list(APPEND cxtpl_outputs "${cxtpl_out_dir}/enum_gen_cpp.cxtpl.cpp")

list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_gen_cpp.cxtpl.cpp")
list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_gen_hpp.cxtpl.cpp")

list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_instance_gen_cpp.cxtpl.cpp")
list(APPEND cxtpl_outputs "${cxtpl_out_dir}/typeclass_instance_gen_hpp.cxtpl.cpp")

