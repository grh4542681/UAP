# messaged
set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/plat)
set(MESSAGE_DEAMON_HRD "${PLAT_INFRA_PATH}/return"
                       "${PLAT_INFRA_PATH}/process"
                       "${PLAT_INFRA_PATH}/file"
                       "${PLAT_INFRA_PATH}/io"
                       "${PLAT_INFRA_PATH}/mempool"
                       "${PLAT_INFRA_PATH}/report"
                       "${PLAT_INFRA_PATH}/thread"
                       "${PLAT_INFRA_PATH}/ipc"
                       "${PLAT_INFRA_PATH}/socket"
                       "${PLAT_INFRA_PATH}/timer"
                       "${PLAT_INFRA_PATH}/container"
                       "${PLAT_INFRA_PATH}/util"
                       "${PLAT_INFRA_PATH}/parser"
                       "${PLAT_INFRA_PATH}/fsm"
                       "${FRAM_PLAT_PATH}/config/lib"
                       "${FRAM_PLAT_PATH}/message/lib"
                       "${3PP_RAPIDJSON_HRD}"
                       "${3PP_YAML_HRD}"
                       "${3PP_PROTOBUF_HRD}"
                       )
set(MESSAGE_DEAMON_SRC message_server.cc
                       message_deamon_main.cc
                       )

add_executable(messaged ${MESSAGE_DEAMON_SRC})
target_include_directories(messaged PRIVATE ${MESSAGE_DEAMON_HRD})
target_link_libraries(messaged libgfile.so libgutil.so libgmsg.so libgfsm.so libgsocket.so libgmp.so libgparser.so libgret.so libgipc.so libgprocess.so libgthread.so libgio.so libgfile.so libgtime.so libgconf.so libgcontainer.so ${3PP_YAML_LIBS} ${3PP_PROTOBUF_LIBS})

