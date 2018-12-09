SET(SOCK_S_TEST_SRC sock_s_test.cc)
ADD_EXECUTABLE(sock_s_test ${SOCK_S_TEST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/module/public/socket" "${FRAM_ROOT_PATH}/module/rm")
TARGET_LINK_LIBRARIES(sock_s_test libgrm.so libgsocket.so)
