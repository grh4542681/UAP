SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)
SET(PARSER_INI_TEST_SRC parser_ini_test.cc)
ADD_EXECUTABLE(parser_ini_test ${PARSER_INI_TEST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/parser")
TARGET_LINK_LIBRARIES(parser_ini_test libgparser.so)

SET(PARSER_JSON_TEST_SRC parser_json_test.cc)
ADD_EXECUTABLE(parser_json_test ${PARSER_JSON_TEST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/parser")
TARGET_LINK_LIBRARIES(parser_json_test libgparser.so)