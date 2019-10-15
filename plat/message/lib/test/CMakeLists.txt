#SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)
INCLUDE_DIRECTORIES(${PLAT_MESSAGE_HRD}
                    "${FRAM_ROOT_PATH}/plat/common")
ADD_EXECUTABLE(msg_agent_test msg_agent_test.cc)
TARGET_LINK_LIBRARIES(msg_agent_test libgmsg.so libgmp.so libgsocket.so libgprocess.so libgthread.so libgtime.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgipc.so libgcontainer.so libgconf.so libgparser.so)
