SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(SYSV_SHM_TEST_SRC sysv_shm_test.cc)
add_executable(sysv_shm_test ${SYSV_SHM_TEST_SRC})

SET(POSIX_SHM_TEST_SRC posix_shm_test.cc)
add_executable(posix_shm_test ${POSIX_SHM_TEST_SRC})

SET(SHM_LIST_TEST_SRC shm_list_test.cc)
add_executable(shm_list_test ${SHM_LIST_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/ipc/")
target_link_libraries(sysv_shm_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
target_link_libraries(posix_shm_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
target_link_libraries(shm_list_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
