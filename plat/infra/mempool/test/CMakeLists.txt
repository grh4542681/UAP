set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(MEMPOOL_TEST_HRD "${PLAT_INFRA_PATH}/return"
                     "${PLAT_INFRA_PATH}/mempool"
                     "${PLAT_INFRA_PATH}/base"
                     "${PLAT_INFRA_PATH}/report"
                     "${PLAT_INFRA_PATH}/file"
                     "${PLAT_INFRA_PATH}/io"
                     )
set(MEMPOOL_TEST_SRC mempool_test.cc)

add_executable(mempool_test ${MEMPOOL_TEST_SRC})
target_include_directories(mempool_test PRIVATE ${MEMPOOL_TEST_HRD})
target_link_libraries(mempool_test libgmp.so libgfile.so libgret.so pthread libgutil.so)
