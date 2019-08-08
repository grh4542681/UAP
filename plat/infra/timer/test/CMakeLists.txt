SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(TIME_C_TEST_SRC time_c_test.cc)
ADD_EXECUTABLE(time_c_test ${TIME_C_TEST_SRC})

TARGET_LINK_LIBRARIES(time_c_test libgtime.so librt.so libgmp.so libgret.so)
