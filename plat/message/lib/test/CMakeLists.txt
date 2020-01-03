set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(COMMON_HRD ${PLAT_MESSAGE_HRD}
             ${PROTOBUF_SRC_PATH}
             "${FRAM_ROOT_PATH}/plat/common")

add_executable(msg_agent_test msg_agent_test.cc)
target_include_directories(msg_agent_test PRIVATE ${COMMON_HRD})
target_link_libraries(msg_agent_test libgmsg.so libgmp.so libgsocket.so libgprocess.so libgthread.so libgtime.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgipc.so libgcontainer.so libgconf.so libgparser.so ${3PP_YAML_LIBS} ${3PP_PROTOBUF_LIBS})

add_executable(msg_builder_test msg_builder_test.cc)
target_include_directories(msg_builder_test PRIVATE ${COMMON_HRD})
target_link_libraries(msg_builder_test libgmsg.so libgmp.so libgsocket.so libgprocess.so libgthread.so libgtime.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgipc.so libgcontainer.so libgconf.so libgparser.so ${3PP_YAML_LIBS} ${3PP_PROTOBUF_LIBS})
