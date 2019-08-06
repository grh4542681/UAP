SET(LIBGRHMP_SRC mempool_return.cc
                 mempool_osproxy.cc
                 mempool_busylist.cc
                 mempool_freelist.cc
                 mempool_center.cc
                 mempool_threadcache.cc
                 mempool_sizemap.cc
                 mempool.cc)
ADD_LIBRARY(GRHmp_SO SHARED ${LIBGRHMP_SRC})
ADD_LIBRARY(GRHmp_A STATIC ${LIBGRHMP_SRC})
TARGET_LINK_LIBRARIES(GRHmp_SO pthread libgret.so)
TARGET_LINK_LIBRARIES(GRHmp_A pthread libgret.so)
SET_TARGET_PROPERTIES(GRHmp_SO PROPERTIES OUTPUT_NAME "gmp" CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(GRHmp_A PROPERTIES OUTPUT_NAME "gmp" CLEAN_DIRECT_OUTPUT 1)
