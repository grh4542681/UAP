set(LIBGREPORT_HRD "${PLAT_INFRA_PATH}/return"
)
set(LIBGREPORT_SRC report_return.cc
)

add_library(GRHreport_SO SHARED ${LIBGREPORT_SRC})
set_target_properties(GRHreport_SO PROPERTIES OUTPUT_NAME "greport" CLEAN_DIRECT_OUTPUT 1)
target_include_directories(GRHreport_SO PRIVATE ${LIBGREPORT_HRD})
if(BUILD_STATIC_LIBS)
    add_library(GRHreport_A STATIC ${LIBGREPORT_SRC})
    set_target_properties(GRHreport_A PROPERTIES OUTPUT_NAME "greport" CLEAN_DIRECT_OUTPUT 1)
    target_include_directories(GRHreport_A PRIVATE ${LIBGREPORT_HRD})
endif()
