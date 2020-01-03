set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(FILE_TEST_HRD "${PLAT_INFRA_PATH}/file"
                  "${PLAT_INFRA_PATH}/return"
                  "${PLAT_INFRA_PATH}/io"
                  "${PLAT_INFRA_PATH}/mempool"
                  "${PLAT_INFRA_PATH}/report"
                  )

set(FILE_TEST_SRC file_test.cc)
add_executable(file_test ${FILE_TEST_SRC})

set(PATH_TEST_SRC path_test.cc)
add_executable(path_test ${PATH_TEST_SRC})

target_include_directories(file_test PRIVATE ${FILE_TEST_HRD})
target_include_directories(path_test PRIVATE ${FILE_TEST_HRD})
target_link_libraries(file_test libgfile.so libgret.so libgutil.so libgmp.so)
target_link_libraries(path_test libgfile.so libgret.so libgutil.so libgmp.so)
