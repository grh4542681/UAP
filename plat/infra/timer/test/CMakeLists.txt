set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(TIMER_TEST_HRD "${PLAT_INFRA_PATH}/timer"
                   "${PLAT_INFRA_PATH}/return"
                   )

set(TIME_C_TEST_SRC time_c_test.cc)
add_executable(time_c_test ${TIME_C_TEST_SRC})
target_include_directories(time_c_test PRIVATE ${TIMER_TEST_HRD})

target_link_libraries(time_c_test libgtime.so librt.so libgmp.so libgret.so)
