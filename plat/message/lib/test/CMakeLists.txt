set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(COMMON_HRD "${PLAT_INFRA_PATH}/return"
               "${PLAT_INFRA_PATH}/base"
               "${PLAT_INFRA_PATH}/parser"
               "${PLAT_INFRA_PATH}/file"
               "${PLAT_INFRA_PATH}/io"
               "${PLAT_INFRA_PATH}/thread"
               "${PLAT_INFRA_PATH}/util"
               "${PLAT_INFRA_PATH}/process"
               "${PLAT_INFRA_PATH}/ipc"
               "${PLAT_INFRA_PATH}/socket"
               "${PLAT_INFRA_PATH}/timer"
               "${PLAT_INFRA_PATH}/mempool"
               "${PLAT_INFRA_PATH}/report"
               "${PLAT_INFRA_PATH}/container"
               "${PLAT_INFRA_PATH}/fsm"
               "${FRAM_PLAT_PATH}/message/lib"
               "${FRAM_PLAT_PATH}/config/lib"
               "${3PP_RAPIDJSON_HRD}"
               "${3PP_YAML_HRD}"
               "${3PP_PROTOBUF_HRD}"
               )

add_executable(msg_agent_test msg_agent_test.cc)
target_include_directories(msg_agent_test PRIVATE ${COMMON_HRD})
target_link_libraries(msg_agent_test libgmsg.so libgfsm.so libgmp.so libgsocket.so libgprocess.so libgthread.so libgtime.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgipc.so libgcontainer.so libgconf.so libgparser.so ${3PP_YAML_LIBS} ${3PP_PROTOBUF_LIBS})

add_executable(msg_builder_test msg_builder_test.cc)
target_include_directories(msg_builder_test PRIVATE ${COMMON_HRD})
target_link_libraries(msg_builder_test libgmsg.so libgfsm.so libgmp.so libgsocket.so libgprocess.so libgthread.so libgtime.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgipc.so libgcontainer.so libgconf.so libgparser.so ${3PP_YAML_LIBS} ${3PP_PROTOBUF_LIBS})
