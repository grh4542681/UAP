SET(LIBGRHTHREAD_SRC thread_info.cc
                     mutex/thread_mutex_lock.cc
                     mutex/thread_rw_lock.cc 
                     )
ADD_LIBRARY(GRHthread_SO SHARED ${LIBGRHTHREAD_SRC})
ADD_LIBRARY(GRHthread_A STATIC ${LIBGRHTHREAD_SRC})
TARGET_LINK_LIBRARIES(GRHthread_SO pthread rt)
TARGET_LINK_LIBRARIES(GRHthread_A pthread rt)
SET_TARGET_PROPERTIES(GRHthread_SO PROPERTIES OUTPUT_NAME "gthread" CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(GRHthread_A PROPERTIES OUTPUT_NAME "gthread" CLEAN_DIRECT_OUTPUT 1)
