SET(LIBGRHCONF_HRD "${PLAT_INFRA_PATH}/return"
                   "${PLAT_INFRA_PATH}/container"
                   "${PLAT_INFRA_PATH}/mempool"
                   "${PLAT_INFRA_PATH}/report"
                   "${PLAT_INFRA_PATH}/file"
                   "${PLAT_INFRA_PATH}/io"
                   "${PLAT_INFRA_PATH}/util"
                   "${PLAT_INFRA_PATH}/parser"
                   "${PLAT_INFRA_PATH}/thread"
                   "${3PP_RAPIDJSON_HRD}"
                   "${3PP_YAML_HRD}"
                   "${3PP_PROTOBUF_HRD}"
                   )
SET(LIBGRHCONF_SRC config_return.cc
                   config_static.cc
                   )

add_library(GRHconf_SO SHARED ${LIBGRHCONF_SRC})
target_include_directories(GRHconf_SO PRIVATE ${LIBGRHCONF_HRD})
set_target_properties(GRHconf_SO PROPERTIES OUTPUT_NAME "gconf" CLEAN_DIRECT_OUTPUT 1)
target_link_libraries(GRHconf_SO rt)

if(BUILD_STATIC_LIBS)
    add_library(GRHconf_A SHARED ${LIBGRHCONF_SRC})
    target_include_directories(GRHconf_A PRIVATE ${LIBGRHCONF_HRD})
    set_target_properties(GRHconf_A PROPERTIES OUTPUT_NAME "gconf" CLEAN_DIRECT_OUTPUT 1)
    target_link_libraries(GRHconf_A rt)
endif()
