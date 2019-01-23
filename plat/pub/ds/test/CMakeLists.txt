SET(TEST_LINK_LIST_SRC test_link_list.cc)
ADD_EXECUTABLE(test_link_list ${TEST_LINK_LIST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/pub/ds" "${FRAM_ROOT_PATH}/plat/pub/mempool")
TARGET_LINK_LIBRARIES(test_link_list libgmp.so)

