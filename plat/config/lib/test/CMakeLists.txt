set(EXECUTABLE_OUTPUT_PATH ${FRAM_BIN_PATH}/test)

set(CONFIG_TEST_HRD "${PLAT_INFRA_PATH}/file"
                    "${PLAT_INFRA_PATH}/return"
                    "${PLAT_INFRA_PATH}/parser"
                    "${PLAT_INFRA_PATH}/io"
                    "${PLAT_INFRA_PATH}/mempool"
                    "${PLAT_INFRA_PATH}/report"
                    "${PLAT_INFRA_PATH}/container"
                    "${PLAT_INFRA_PATH}/util"
                    "${PLAT_INFRA_PATH}/thread"
                    "${FRAM_PLAT_PATH}/config/lib"
                    "${3PP_RAPIDJSON_HRD}"
                    "${3PP_YAML_HRD}"
                    "${3PP_PROTOBUF_HRD}"
                    )

add_executable(static_config_test static_config_test.cc)
target_include_directories(static_config_test PRIVATE ${CONFIG_TEST_HRD})
target_link_libraries(static_config_test libgconf.so libgmp.so -lrt libgret.so libgfile.so libgio.so libgutil.so libgcontainer.so libgparser.so libgthread.so libgprocess.so libgsocket.so libgmsg.so libgio.so libyaml-cpp.so)
