SET(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

SET(PROCESS_TEST_SRC process_test.cc)
add_executable(process_test ${PROCESS_TEST_SRC})

SET(PROCESS_SINGLE_TEST_SRC process_single_test.cc)
add_executable(process_single_test ${PROCESS_SINGLE_TEST_SRC})

INCLUDE_DIRECTORIES("${FRAM_ROOT_PATH}/plat/infra/process")
target_link_libraries(process_test libgprocess.so libgfile.so libgmp.so libgsocket.so libgutil.so libgthread.so libgret.so libgtime.so libgmsg.so libgio.so libgipc.so libgconf.so libgcontainer.so libgparser.so libyaml-cpp.so)
target_link_libraries(process_single_test libgprocess.so libgfile.so libgmp.so libgsocket.so libgutil.so libgthread.so libgret.so libgtime.so libgmsg.so libgio.so libgipc.so libgconf.so libgcontainer.so libgparser.so libyaml-cpp.so)
