file(STRINGS proto.list PROTOFILES)
foreach(PROTOFILE ${PROTOFILES})
    message("Generating cpp source file of ${PROTOFILE} ...")
    execute_process(COMMAND ${3PP_PROTOBUF_CPP_GEN}
                            ${3PP_PROTOBUF_CPP_INCLUDE}=${CMAKE_CURRENT_SOURCE_DIR}
                            ${3PP_PROTOBUF_CPP_OUTPUT}=${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/${PROTOFILE}
                            RESULT_VARIABLE RESULT)
    if(NOT(${RESULT} EQUAL 0))
        message(FATAL_ERROR "Result (${RESULT})")
    endif()
    string(REGEX REPLACE ".proto$" ".pb.cc" PROTOFILECPP ${PROTOFILE})
    string(APPEND PROTOFILECPPS ";" ${CMAKE_CURRENT_SOURCE_DIR}/${PROTOFILECPP})
endforeach(PROTOFILE)

set(MESSAGE_PROTOBUF_SRC ${PROTOFILECPPS} PARENT_SCOPE)
