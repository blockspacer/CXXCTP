# files for codegen

#add_subdirectory(resources/ctp_scripts/2_scripts/typeclass_instance)
#add_subdirectory(resources/ctp_scripts/2_scripts/typeclass)
#add_subdirectory(resources/ctp_scripts/2_scripts/reflect_enum)

if(BUNDLE_EXAMPLE_SCRIPTS)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass_instance)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/typeclass_combo)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/reflect_enum)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/make_removefuncbody)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple/ctp_scripts/2_scripts/make_interface)
endif(BUNDLE_EXAMPLE_SCRIPTS)
