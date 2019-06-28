SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(BITMAP_TEST_SRC bitmap_test.cc)
ADD_EXECUTABLE(bitmap_test ${BITMAP_TEST_SRC})

TARGET_LINK_LIBRARIES(bitmap_test libgutil.so librt.so libgmp.so)
