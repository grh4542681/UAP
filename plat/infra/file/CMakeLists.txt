set(LIBGRHFILEOP_HRD "${PLAT_INFRA_PATH}/return"
                     "${PLAT_INFRA_PATH}/base"
                     "${PLAT_INFRA_PATH}/util"
                     "${PLAT_INFRA_PATH}/io"
                     "${PLAT_INFRA_PATH}/mempool"
                     "${PLAT_INFRA_PATH}/report"
                     )
set(LIBGRHFILEOP_SRC file_return.cc
                     file_api.cc
                     file_fd.cc
                     file.cc
                     file_path.cc
                     )
add_library(GRHfileop_SO SHARED ${LIBGRHFILEOP_SRC})
target_include_directories(GRHfileop_SO PRIVATE ${LIBGRHFILEOP_HRD})
target_link_libraries(GRHfileop_SO pthread)
set_target_properties(GRHfileop_SO PROPERTIES OUTPUT_NAME "gfile" CLEAN_DIRECT_OUTPUT 1)

if(BUILD_STATIC_LIBS)
    add_library(GRHfileop_A STATIC ${LIBGRHFILEOP_SRC})
    target_include_directories(GRHfileop_A PRIVATE ${LIBGRHFILEOP_HRD})
    target_link_libraries(GRHfileop_A pthread)
    set_target_properties(GRHfileop_A PROPERTIES OUTPUT_NAME "gfile" CLEAN_DIRECT_OUTPUT 1)
endif()
