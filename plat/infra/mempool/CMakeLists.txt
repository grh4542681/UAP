set(LIBGRHMP_HRD "${PLAT_INFRA_PATH}/report"
                 "${PLAT_INFRA_PATH}/base"
                 "${PLAT_INFRA_PATH}/return"
                 "${PLAT_INFRA_PATH}/file"
                 "${PLAT_INFRA_PATH}/io"
                 "${PLAT_INFRA_PATH}/mempool"
                 )
set(LIBGRHMP_SRC mempool_return.cc
                 mempool_osproxy.cc
                 mempool_busylist.cc
                 mempool_freelist.cc
                 mempool_center.cc
                 mempool_threadcache.cc
                 mempool_sizemap.cc
                 mempool.cc
                 mempool_alloctor.cc
                 )

add_library(GRHmp_SO SHARED ${LIBGRHMP_SRC})
set_target_properties(GRHmp_SO PROPERTIES OUTPUT_NAME "gmp" CLEAN_DIRECT_OUTPUT 1)
target_include_directories(GRHmp_SO PRIVATE ${LIBGRHMP_HRD})
target_link_libraries(GRHmp_SO pthread)

if(BUILD_STATIC_LIBS)
    add_library(GRHmp_A STATIC ${LIBGRHMP_SRC})
    set_target_properties(GRHmp_A PROPERTIES OUTPUT_NAME "gmp" CLEAN_DIRECT_OUTPUT 1)
    target_include_directories(GRHmp_A PRIVATE ${LIBGRHMP_HRD})
    target_link_libraries(GRHmp_A pthread)
endif()
