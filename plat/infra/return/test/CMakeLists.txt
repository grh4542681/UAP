set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(RETURN_TEST_HRD "${PLAT_INFRA_PATH}/return")
set(RETURN_TEST_SRC return_test.cc)

add_executable(return_test ${RETURN_TEST_SRC})
target_include_directories(return_test PRIVATE ${RETURN_TEST_HRD})
target_link_libraries(return_test libgret.so)
