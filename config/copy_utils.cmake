set(DEFAULT_TARGETS "")

set(DEFAULT_BIN_LOC "/usr/local/bin")

macro(copy SRC DST)
  set(TEMPDST "${CMAKE_CURRENT_BINARY_DIR}/${DST}")
  set(TEMPSRC "${CMAKE_CURRENT_SOURCE_DIR}/${SRC}")
  set(DEFAULT_TARGETS ${DEFAULT_TARGETS} ${TEMPDST})
  add_custom_command(
    OUTPUT ${TEMPDST}
    COMMAND ${CMAKE_COMMAND} -E copy ${TEMPSRC} ${TEMPDST}
    DEPENDS ${TEMPSRC}
  )
endmacro()

macro(genCopy)
  add_custom_target(
    ${PROJECT_NAME} ALL
    DEPENDS ${DEFAULT_TARGETS}
  )
endmacro()
