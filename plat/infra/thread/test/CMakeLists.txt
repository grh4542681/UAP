SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(THREAD_TEST_SRC thread_test.cc)
ADD_EXECUTABLE(thread_test ${THREAD_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/thread")
TARGET_LINK_LIBRARIES(thread_test libgthread.so libgprocess.so libgfile.so libgipc.so libgmp.so libgsocket.so libgtime.so -lpthread)
