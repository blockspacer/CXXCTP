macro(conditional_remove ARG_DO_REMOVE ARG_DIR ARG_WORKING_DIR)
  if(${ARG_DO_REMOVE})
    if (NOT EXISTS ${ARG_DIR})
      message(STATUS "not existent: ${ARG_DIR}" --yellow --bold)
    endif (NOT EXISTS ${ARG_DIR})

    if(IS_DIRECTORY ${ARG_DIR})
      execute_process(
        COMMAND ${CMAKE_COMMAND} "-E" "remove_directory" "${ARG_DIR}"
        WORKING_DIRECTORY ${ARG_WORKING_DIR}
        TIMEOUT 7200 # sec
      )
      message(STATUS "removed old directory ${ARG_DIR}" --yellow --bold)
      if (EXISTS ${ARG_DIR})
        message(STATUS "can`t remove directory ${ARG_DIR}" --red --bold)
      endif(EXISTS ${ARG_DIR})
    else(IS_DIRECTORY ${ARG_DIR})
      execute_process(
        COMMAND ${CMAKE_COMMAND} "-E" "remove" "${ARG_DIR}"
        WORKING_DIRECTORY ${ARG_WORKING_DIR}
        TIMEOUT 7200 # sec
      )
      message(STATUS "removed old file ${ARG_DIR}" --yellow --bold)
      if (EXISTS ${ARG_DIR})
        message(STATUS "can`t remove file ${ARG_DIR}" --red --bold)
      endif(EXISTS ${ARG_DIR})
    endif(IS_DIRECTORY ${ARG_DIR})
  else(${ARG_DO_REMOVE})
    message(STATUS "kept old path: ${ARG_DIR}" --yellow --bold)
  endif(${ARG_DO_REMOVE})
endmacro(conditional_remove)
