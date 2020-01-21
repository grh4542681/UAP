set(MESSAGE_PROTOBUF_SRC)
add_subdirectory(protobuf)

set(LIBGRHMSG_HRD "${PLAT_INFRA_PATH}/return"
                  "${PLAT_INFRA_PATH}/process"
                  "${PLAT_INFRA_PATH}/ipc"
                  "${PLAT_INFRA_PATH}/socket"
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
                  "${3PP_RAPIDJSON_HRD}"
                  "${3PP_YAML_HRD}"
                  "${3PP_PROTOBUF_HRD}"
                  )

set(LIBGRHMSG_SRC message_return.cc
                  message_raw.cc
                  message_appid.cc
                  message_stream.cc
                  message_api.cc
                  message_agent.cc
                  message_listener.cc
                  message_endpoint.cc
                  message_remote.cc
                  message_manager.cc
#                  message_heartbeat.cc
#                  message_heartbeat_element.cc
                  ${MESSAGE_PROTOBUF_SRC}
                  )

add_library(GRHmsg_SO SHARED ${LIBGRHMSG_SRC})
set_target_properties(GRHmsg_SO PROPERTIES OUTPUT_NAME "gmsg" CLEAN_DIRECT_OUTPUT 1)
target_include_directories(GRHmsg_SO PRIVATE ${LIBGRHMSG_HRD})
target_link_libraries(GRHmsg_SO rt)

if(BUILD_STATIC_LIBS)
    add_library(GRHmsg_A STATIC ${LIBGRHMSG_SRC})
    set_target_properties(GRHmsg_A PROPERTIES OUTPUT_NAME "gmsg" CLEAN_DIRECT_OUTPUT 1)
    target_include_directories(GRHmsg_A PRIVATE ${LIBGRHMSG_HRD})
endif()
