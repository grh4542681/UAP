SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(PROCESS_TEST_SRC process_test.cc)
ADD_EXECUTABLE(process_test ${PROCESS_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/process")
TARGET_LINK_LIBRARIES(process_test libgprocess.so libgfile.so)
