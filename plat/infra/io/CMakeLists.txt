set(LIBGIO_HRD "${PLAT_INFRA_PATH}/return"
               "${PLAT_INFRA_PATH}/base"
               "${PLAT_INFRA_PATH}/report"
               "${PLAT_INFRA_PATH}/mempool"
               "${PLAT_INFRA_PATH}/timer"
               "${PLAT_INFRA_PATH}/process"
               "${PLAT_INFRA_PATH}/thread"
               "${PLAT_INFRA_PATH}/io"
               )
set(LIBGIO_SRC io_return.cc
               io_fd.cc
               io_select.cc
               io_auto_select.cc
               io_select_item.cc
               io_epoll_fd.cc
               )

add_library(GRHio_SO SHARED ${LIBGIO_SRC})
set_target_properties(GRHio_SO PROPERTIES OUTPUT_NAME "gio" CLEAN_DIRECT_OUTPUT 1)
target_include_directories(GRHio_SO PRIVATE ${LIBGIO_HRD})

if(BUILD_STATIC_LIBS)
    add_library(GRHio_A STATIC ${LIBGIO_SRC})
    set_target_properties(GRHio_A PROPERTIES OUTPUT_NAME "gio" CLEAN_DIRECT_OUTPUT 1)
    target_include_directories(GRHio_A PRIVATE ${LIBGIO_HRD})
endif()
