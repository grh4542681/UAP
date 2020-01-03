SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(SYSV_SEM_TEST_SRC sysv_sem_test.cc)
add_executable(sysv_sem_test ${SYSV_SEM_TEST_SRC})
target_link_libraries(sysv_sem_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})

SET(POSIX_SEM_TEST_SRC posix_sem_test.cc)
add_executable(posix_sem_test ${POSIX_SEM_TEST_SRC})
target_link_libraries(posix_sem_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})

SET(MUTEX_SEM_TEST_SRC mutex_sem_test.cc)
add_executable(mutex_sem_test ${MUTEX_SEM_TEST_SRC})
target_link_libraries(mutex_sem_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})

SET(RWLOCK_SEM_TEST_SRC rwlock_sem_test.cc)
add_executable(rwlock_sem_test ${RWLOCK_SEM_TEST_SRC})
target_link_libraries(rwlock_sem_test ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
SET(RWLOCK_SEM_TEST_SRC1 rwlock_sem_test1.cc)
add_executable(rwlock_sem_test1 ${RWLOCK_SEM_TEST_SRC1})
target_link_libraries(rwlock_sem_test1 ${COMM_OS_LIB} ${PLAT_INFRA_LIB})
