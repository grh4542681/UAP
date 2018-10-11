SET(SYSV_SEM_TEST_SRC sysv_sem_test.cc)
ADD_EXECUTABLE(sysv_sem_test ${SYSV_SEM_TEST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/module/public/ipc")
TARGET_LINK_LIBRARIES(sysv_sem_test libgipc.so)
