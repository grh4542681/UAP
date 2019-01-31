SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)
SET(TEST_LINK_LIST_SRC test_link_list.cc)
SET(TEST_HASH_TABLE_SEC test_hash_table.cc)
ADD_EXECUTABLE(test_link_list ${TEST_LINK_LIST_SRC})
ADD_EXECUTABLE(test_hash_table ${TEST_HASH_TABLE_SEC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/pub/ds" "${FRAM_ROOT_PATH}/plat/pub/mempool" "${FRAM_ROOT_PATH}/plat/pub/thread")
TARGET_LINK_LIBRARIES(test_link_list libgmp.so pthread libgthread.so)
TARGET_LINK_LIBRARIES(test_hash_table libgmp.so pthread libgthread.so)

