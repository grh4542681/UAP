SET(PARSER_INI_TEST_SRC parser_ini_test.cc)
ADD_EXECUTABLE(parser_ini_test ${PARSER_INI_TEST_SRC})
INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/pub/parser" "${FRAM_ROOT_PATH}/plat/pub/mempool")
TARGET_LINK_LIBRARIES(parser_ini_test libgparser.so rt libgmp.so)
