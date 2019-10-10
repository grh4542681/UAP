SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(FILE_TEST_SRC file_test.cc)
ADD_EXECUTABLE(file_test ${FILE_TEST_SRC})

SET(PATH_TEST_SRC path_test.cc)
ADD_EXECUTABLE(path_test ${PATH_TEST_SRC})

TARGET_LINK_LIBRARIES(file_test libgfile.so libgret.so libgutil.so libgmp.so)
TARGET_LINK_LIBRARIES(path_test libgfile.so libgret.so libgutil.so libgmp.so)
