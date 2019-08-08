# messaged
SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/plat)
SET(MESSAGE_DEAMON_SRC src/message_deamon.cc
                       src/message_deamon_main.cc
                       )
ADD_EXECUTABLE(messaged ${MESSAGE_DEAMON_SRC})
INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD})
TARGET_LINK_LIBRARIES(messaged libgmsg.so libgret.so ${COMM_OS_LIB} ${PLAT_INFRA_LIB} libgthread.so)

