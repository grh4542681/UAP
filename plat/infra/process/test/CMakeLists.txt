SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(PROCESS_TEST_SRC process_test.cc)
ADD_EXECUTABLE(process_test ${PROCESS_TEST_SRC})

SET(PROCESS_SINGLE_TEST_SRC process_single_test.cc)
ADD_EXECUTABLE(process_single_test ${PROCESS_SINGLE_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/process")
TARGET_LINK_LIBRARIES(process_test libgprocess.so libgfile.so libgipc.so libgmp.so libgsocket.so libgutil.so libgthread.so libgret.so libgtime.so libgmsg.so libgio.so)
TARGET_LINK_LIBRARIES(process_single_test libgprocess.so libgfile.so libgipc.so libgmp.so libgsocket.so libgutil.so libgthread.so libgret.so libgtime.so libgmsg.so libgio.so)
