set(DEFAULT_TARGETS "")

#set CMAKE_JAVA_INCLUDE_PATH
include(../config/java_paths.cmake)

macro(add_java_src SRCCODE)
    STRING(REGEX REPLACE "[.]java" ".class" CLASSFILE "${SRCCODE}")
    set(DEFAULT_TARGETS ${DEFAULT_TARGETS} ${CLASSFILE})
    MESSAGE(STATUS "Output .class file is: ${CLASSFILE}")
    add_custom_command(
        OUTPUT ${CLASSFILE}
        COMMAND ${JAVAC_EXECUTABLE}
        -classpath "${CMAKE_JAVA_INCLUDE_PATH}:${CMAKE_CURRENT_SOURCE_DIR}"
        -d ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRCCODE}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SRCCODE}
    )
endmacro()

macro(compileGUI)
    add_custom_target(
        ${PROJECT_NAME} ALL
        DEPENDS ${DEFAULT_TARGETS}
    )
endmacro()
