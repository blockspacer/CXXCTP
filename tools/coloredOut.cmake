#
# Colored print to terminal, uses "cmake_echo_color"
#
# WHY? see https://stackoverflow.com/a/36233927/10904212
# NOTE: if you print to file - disable "HAS_COLORED_OUTPUT"
#
# SUPPORTED COLORS: see https://github.com/Kitware/CMake/blob/master/Source/cmcmd.cxx#L1408
#
# options (only ON/OFF):
# * DISABLE_COLORED_OUTPUT
# * HAS_COLORED_OUTPUT
# vars:
# * TOGGLE_COLORED_OUTPUT ("true"/"false")
# * SHOW_ICONS (TRUE/FALSE)
# macros:
# * colored_print
# * colored_fatal
# * colored_ok
# * colored_warn
# * colored_notify

cmake_minimum_required(VERSION 3.5)

# switches to cmake message() system (preferred)
option(HAS_COLORED_OUTPUT "is running from terminal" ON)

if(HAS_COLORED_OUTPUT)
  # WHY CLICOLOR_FORCE? see https://stackoverflow.com/a/36233927/10904212
  set(COLORED_OUTPUT_ENABLER "${CMAKE_COMMAND}" "-E" "env" "CLICOLOR_FORCE=1")
else(HAS_COLORED_OUTPUT)
  set(COLORED_OUTPUT_ENABLER "")
endif(HAS_COLORED_OUTPUT)

# NOTE: not recommended, see HAS_COLORED_OUTPUT
option(DISABLE_COLORED_OUTPUT "full disable of output" OFF)

option(LOG_ALL_COLORED_OUTPUT "only for debug in-dev purposes" OFF)

# see "--switch=" at https://github.com/Kitware/CMake/blob/master/Source/cmcmd.cxx#L1395
set(TOGGLE_COLORED_OUTPUT "true")

set(SHOW_ICONS TRUE)
set(CROSS_ICON "✘")
set(OK_ICON "✔")
set(NOTIFY_ICON "(!)")
set(WARN_ICON "(!!!)")

# As of CMake 3.5, cmake_parse_arguments becomes a builtin command (written in C++ instead of CMake)
# include(CMakeParseArguments) is no longer required but, for now, the file CMakeParseArguments.cmake is kept empty for compatibility.
include(CMakeParseArguments)

# NOTE: not public implementation
#
# Function
#   colored_print_implementation(MESSAGE <...> (PARAMS <...>))
#
# Example:
#   colored_print_implementation(MESSAGE "hello world;13.,fga")
#   colored_print_implementation(MESSAGE "hello world;13.,fga" PARAMS --red --bold)
function(colored_print_implementation)
  # see https://cliutils.gitlab.io/modern-cmake/chapters/basics/functions.html
  #set(options ) # empty
  #set(oneValueArgs ) # empty
  set(multiValueArgs PARAMS MESSAGE )
  #
  cmake_parse_arguments(
    ARGUMENTS # prefix of output variables
    "${options}" # list of names of the boolean arguments (only defined ones will be true)
    "${oneValueArgs}" # list of names of mono-valued arguments
    "${multiValueArgs}" # list of names of multi-valued arguments (output variables are lists)
    ${ARGN} # arguments of the function to parse, here we take the all original ones
  )
  #
  set(MESSAGE ${ARGUMENTS_MESSAGE})
  #
  set(PARAMS ${ARGUMENTS_PARAMS})
  #
  set(dependencies "")
  if(ARGUMENTS_DEPENDENCIES)
    set(dependencies ${ARGUMENTS_UNPARSED_ARGUMENTS})
  endif()
  #
  if(LOG_ALL_COLORED_OUTPUT)
    message(STATUS "Provided ARGN are:")
    foreach(src ${ARGN})
        message(STATUS "- ${src}")
    endforeach(src)
    message(STATUS "dependencies=${dependencies}")
    message(STATUS "MESSAGE=${MESSAGE}")
    message(STATUS "PARAMS=${PARAMS}")
  endif(LOG_ALL_COLORED_OUTPUT)
  #
  if(NOT DISABLE_COLORED_OUTPUT)
    if(HAS_COLORED_OUTPUT)
      execute_process(COMMAND
        ${COLORED_OUTPUT_ENABLER}
          # see https://github.com/Kitware/CMake/blob/master/Source/cmcmd.cxx#L1408
          ${CMAKE_COMMAND} -E cmake_echo_color ${PARAMS} --switch=${TOGGLE_COLORED_OUTPUT} "${MESSAGE}"
      )
    else(HAS_COLORED_OUTPUT)
      message(STATUS ${MESSAGE})
    endif(HAS_COLORED_OUTPUT)
  endif(NOT DISABLE_COLORED_OUTPUT)
endfunction()

# deprecated: can`t handle complex lists, see colored_print_implementation
# example: colored_print("hello world" --red --bold)
#macro(colored_print MESSAGE)
#  if(NOT DISABLE_COLORED_OUTPUT)
#    if(HAS_COLORED_OUTPUT)
#      execute_process(COMMAND
#        ${COLORED_OUTPUT_ENABLER}
#          # see https://github.com/Kitware/CMake/blob/master/Source/cmcmd.cxx#L1408
#          ${CMAKE_COMMAND} -E cmake_echo_color ${ARGN} --switch=${TOGGLE_COLORED_OUTPUT} ${MESSAGE}
#      )
#    else(HAS_COLORED_OUTPUT)
#      message(STATUS ${MESSAGE})
#    endif(HAS_COLORED_OUTPUT)
#  endif(NOT DISABLE_COLORED_OUTPUT)
#endmacro(colored_print)

# example: colored_print("hello world" --red --bold)
macro(colored_print MESSAGE)
  if(NOT DISABLE_COLORED_OUTPUT)
    colored_print_implementation(MESSAGE ${MESSAGE} PARAMS ${ARGN})
  endif(NOT DISABLE_COLORED_OUTPUT)
endmacro(colored_print)

# example: colored_fatal("hello world" --red --bold)
macro(colored_fatal MESSAGE)
  if(NOT DISABLE_COLORED_OUTPUT)
    if(SHOW_ICONS)
      colored_print_implementation(MESSAGE "${CROSS_ICON} " PARAMS --red --bold --no-newline)
    endif(SHOW_ICONS)
    colored_print_implementation(MESSAGE ${MESSAGE} PARAMS ${ARGN})
    message(FATAL_ERROR ${MESSAGE})
  endif(NOT DISABLE_COLORED_OUTPUT)
endmacro(colored_fatal)

# example: colored_ok("hello world" --green --bold)
macro(colored_ok MESSAGE)
  if(NOT DISABLE_COLORED_OUTPUT)
    if(SHOW_ICONS)
      colored_print_implementation(MESSAGE "${OK_ICON} " PARAMS --green --bold --no-newline)
    endif(SHOW_ICONS)
    colored_print_implementation(MESSAGE ${MESSAGE} PARAMS ${ARGN})
  endif(NOT DISABLE_COLORED_OUTPUT)
endmacro(colored_ok)

# example: colored_warn("hello world" --yellow --bold)
macro(colored_warn MESSAGE)
  if(NOT DISABLE_COLORED_OUTPUT)
    if(SHOW_ICONS)
      colored_print_implementation(MESSAGE "${WARN_ICON} " PARAMS --yellow --bold --no-newline)
    endif(SHOW_ICONS)
    colored_print_implementation(MESSAGE ${MESSAGE} PARAMS ${ARGN})
    message(WARNING ${MESSAGE})
  endif(NOT DISABLE_COLORED_OUTPUT)
endmacro(colored_warn)

# example: colored_notify("hello world" --yellow --bold)
macro(colored_notify MESSAGE)
  if(NOT DISABLE_COLORED_OUTPUT)
    if(SHOW_ICONS)
      colored_print_implementation(MESSAGE "${NOTIFY_ICON} " PARAMS --yellow --bold --no-newline)
    endif(SHOW_ICONS)
    colored_print_implementation(MESSAGE ${MESSAGE} PARAMS ${ARGN})
  endif(NOT DISABLE_COLORED_OUTPUT)
endmacro(colored_notify)
