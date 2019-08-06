SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(MEMPOOL_TEST_SRC mempool_test.cc)
ADD_EXECUTABLE(mempool_test ${MEMPOOL_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/mempool" "${FRAM_ROOT_PATH}/plat/infra/file" "${FRAM_ROOT_PATH}/plat/infra/report")
TARGET_LINK_LIBRARIES(mempool_test libgmp.so libgfile.so libgret.so pthread)
