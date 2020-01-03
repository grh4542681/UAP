SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(MSG_SHM_TEST_SRC msg_shm_test.cc)
add_executable(msg_shm_test ${MSG_SHM_TEST_SRC})

SET(MSG_SHM_TEST2_SRC msg_shm_test2.cc)
add_executable(msg_shm_test2 ${MSG_SHM_TEST2_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/ipc/")
target_link_libraries(msg_shm_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
target_link_libraries(msg_shm_test2 ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
