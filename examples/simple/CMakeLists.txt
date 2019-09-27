cmake_minimum_required( VERSION 3.10.0 FATAL_ERROR )

# Building as separate project.
project(CXXCTP_example)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

set(CXXCTP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")
list(APPEND CMAKE_MODULE_PATH ${CXXCTP_DIR}/cmake/exports)

#
# If you have built boost statically you will need to set the Boost_USE_STATIC_LIBS CMake variable to ON
# also don`t forget to set DBOOST_LOG_DYN_LINK https://stackoverflow.com/a/17868918/10904212
# set( Boost_USE_STATIC_LIBS FALSE )
# set( Boost_USE_STATIC_RUNTIME FALSE )
# set( Boost_USE_MULTITHREADED TRUE )
set( BOOST_ROOT CACHE STRING /usr )
set( Boost_ADDITIONAL_VERSIONS "1.62 1.63 1.64 1.65 1.66 1.67 1.68 1.69" )
set( BOOST_LIBS CACHE STRING ${BOOST_ROOT}/lib )
# set( Boost_COMPILER "-gcc" )
find_package( Boost
  COMPONENTS program_options filesystem regex date_time system thread graph log
  EXACT REQUIRED )

find_package( Threads REQUIRED )
message(STATUS "CMAKE_THREAD_LIBS_INIT = ${CMAKE_THREAD_LIBS_INIT}")

find_package( X11 REQUIRED )
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

find_package( EXPAT REQUIRED )
message(STATUS "EXPAT_LIBRARIES = ${EXPAT_LIBRARIES}")

find_package( ZLIB REQUIRED )
message(STATUS "ZLIB_LIBRARIES = ${ZLIB_LIBRARIES}")

message(STATUS "CMAKE_DL_LIBS = ${CMAKE_DL_LIBS}")

# The project has one binary:
add_executable(CXXCTP_example
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_app.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Spell_WaterSpell.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Spell_FireSpell.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MagicItem_WaterSpell.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MagicItem_FireSpell.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Printable_WaterSpell.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Printable_FireSpell.cpp
)

set( USED_SYSTEM_LIBS
  Threads::Threads # pthread, https://cmake.org/cmake/help/v3.13/module/FindThreads.html
  #${X11_LIBRARIES} # https://cmake.org/cmake/help/v3.13/module/FindX11.html
  #${CMAKE_DL_LIBS} # https://cmake.org/cmake/help/v3.13/variable/CMAKE_DL_LIBS.html
  #EXPAT::EXPAT # https://cmake.org/cmake/help/v3.13/module/FindEXPAT.html
  #ZLIB::ZLIB # https://cmake.org/cmake/help/v3.13/module/FindZLIB.html
  # Custom libs
  stdc++fs # C++17 std::filesystem
  CACHE INTERNAL "USED_SYSTEM_LIBS" )

target_link_libraries(CXXCTP_example PUBLIC
  # system libs
  ${USED_SYSTEM_LIBS}
)

target_include_directories(CXXCTP_example PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen
  ${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/1_typeclasses
  ${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/2_typeclass_instances
  ${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/3_typeclass_combinations
  ${CMAKE_CURRENT_SOURCE_DIR}/src/codegen_helpers # path to type_erasure_common.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/ctp_scripts
  ${CMAKE_CURRENT_SOURCE_DIR}/generated
)


set_target_properties(CXXCTP_example
  PROPERTIES ENABLE_EXPORTS 1)


if(NOT BUNDLE_EXAMPLE_SCRIPTS)
  # generate cxtpl
  add_subdirectory(ctp_scripts/2_scripts/typeclass_instance)
  add_subdirectory(ctp_scripts/2_scripts/typeclass)
  add_subdirectory(ctp_scripts/2_scripts/typeclass_combo)
  add_subdirectory(ctp_scripts/2_scripts/reflect_enum)
  add_subdirectory(ctp_scripts/2_scripts/make_removefuncbody)
  add_subdirectory(ctp_scripts/2_scripts/make_interface)
endif(NOT BUNDLE_EXAMPLE_SCRIPTS)

find_package(CXXCTP_tool REQUIRED)

list(APPEND CXXCTP_inputs
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/test.cpp")
list(APPEND CXXCTP_inputs
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/ReflShapeKind.hpp")

# NOTE: `typeclasses` must load before `typeclass_instances`
# and `typeclass_combinations`,
# so we added `1_`, `2_`, ... before folder names.
list(APPEND CXXCTP_inputs
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/1_typeclasses/MagicItem_typeclass.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/1_typeclasses/Printable_typeclass.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/1_typeclasses/Spell_typeclass.hpp"
)
list(APPEND CXXCTP_inputs
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/2_typeclass_instances/FireSpell_typeclass_instances.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/2_typeclass_instances/WaterSpell_typeclass_instances.hpp"
)
list(APPEND CXXCTP_inputs
  "${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/3_typeclass_combinations/Spell_MagicItem_typeclass_combo.hpp"
)

# dir to generated files
list(APPEND CXXCTP_outdir "${CMAKE_CURRENT_SOURCE_DIR}/generated")

add_dependencies(CXXCTP_example CXXCTP_tool)

set(CXXCTP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../..")

set(CLING_BUILD_DIR "${CXXCTP_DIR}/cling-build")

# create new codegen files for TARGET_NAME_HERE based on CXXCTP_inputs and CXXCTP_outdir
set(CXXCTP_tool_HINTS "${CXXCTP_DIR}/build/tool")

macro(append_absolute_path_to_extras PATH OUT_VAR)
  get_filename_component(TMP_PATH_TO_ABSOLUTE
                         "${PATH}"
                         ABSOLUTE)
  list(APPEND ${OUT_VAR} "-extra-arg=-I${TMP_PATH_TO_ABSOLUTE}")
endmacro(append_absolute_path_to_extras)

# make include files from project dirs visible to Clang/Cling
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/1_typeclasses" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/2_typeclass_instances" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src/for_codegen/3_typeclass_combinations" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/src/codegen_helpers" EXTRA_ARGS) # path to type_erasure_common.hpp
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/include" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/ctp_scripts" EXTRA_ARGS)
append_absolute_path_to_extras("${CMAKE_CURRENT_SOURCE_DIR}/generated" EXTRA_ARGS)

# EXTRA_ARGS for CXXCTP_tool: clang paths for cling
append_absolute_path_to_extras("${CXXCTP_DIR}/include" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/build/include" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/build/lib/clang/5.0.0/include" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/src/include" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/src/tools/clang/include/" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/build/tools/clang/include/" EXTRA_ARGS)
append_absolute_path_to_extras("${CLING_BUILD_DIR}/src/tools/cling/include/" EXTRA_ARGS)

# run CXXCTP_tool
target_add_CXXCTP_tool(CXXCTP_example
  "CXXCTP_example_simple" "${CXXCTP_inputs}" "${CXXCTP_outdir}" "${EXTRA_ARGS}")

