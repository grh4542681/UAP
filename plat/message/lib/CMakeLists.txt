SET(LIBGRHMSG_SRC ../message_return.cc
                  message_type.cc
                  message_api.cc
                  message_agent.cc
                  message_listener.cc
                  )
INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD}
                    "${FRAM_ROOT_PATH}/plat/common"
                    "${FRAM_ROOT_PATH}/plat/infra/ipc"
                    "${FRAM_ROOT_PATH}/plat/infra/socket"
                    )
ADD_LIBRARY(GRHmsg_SO SHARED ${LIBGRHMSG_SRC})
SET_TARGET_PROPERTIES(GRHmsg_SO PROPERTIES OUTPUT_NAME "gmsg" CLEAN_DIRECT_OUTPUT 1)
TARGET_LINK_LIBRARIES(GRHmsg_SO rt)

