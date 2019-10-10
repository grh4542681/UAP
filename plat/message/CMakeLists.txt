# messaged
SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/plat)
SET(MESSAGE_DEAMON_SRC src/message_server.cc
                       src/message_deamon_main.cc
                       )
ADD_EXECUTABLE(messaged ${MESSAGE_DEAMON_SRC})
INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD})
TARGET_LINK_LIBRARIES(messaged libgfile.so libgutil.so libgmsg.so libgsocket.so libgmp.so libgparser.so libgret.so libgprocess.so libgthread.so libgio.so libgfile.so)

