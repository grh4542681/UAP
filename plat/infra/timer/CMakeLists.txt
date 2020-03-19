set(LIBGTIME_HRD "${PLAT_INFRA_PATH}/return"
                 "${PLAT_INFRA_PATH}/base"
                 "${PLAT_INFRA_PATH}/io"
                 "${PLAT_INFRA_PATH}/mempool"
                 "${PLAT_INFRA_PATH}/report"
                 "${PLAT_INFRA_PATH}/thread"
                 "${PLAT_INFRA_PATH}/process"
                 "${PLAT_INFRA_PATH}/timer"
                 )
set(LIBGTIME_SRC timer_return.cc
                 timer_fd.cc
                 timer_timer.cc
)

add_library(GRHtime_SO SHARED ${LIBGTIME_SRC})
set_target_properties(GRHtime_SO PROPERTIES OUTPUT_NAME "gtime" CLEAN_DIRECT_OUTPUT 1)
target_include_directories(GRHtime_SO PRIVATE ${LIBGTIME_HRD})

if(BUILD_STATIC_LIBS)
    add_library(GRHtime_A STATIC ${LIBGTIME_SRC})
    set_target_properties(GRHtime_A PROPERTIES OUTPUT_NAME "gtime" CLEAN_DIRECT_OUTPUT 1)
    target_include_directories(GRHtime_A PRIVATE ${LIBGTIME_HRD})
endif()
