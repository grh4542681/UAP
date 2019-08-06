SET(LIBGRHTHREAD_SRC thread_return.cc
                     thread_id.cc
                     thread_info.cc
                     mutex/thread_mutex_lock.cc
                     mutex/thread_rw_lock.cc 
                     signal/thread_signal_ctrl.cc
                     )
ADD_LIBRARY(GRHthread_SO SHARED ${LIBGRHTHREAD_SRC})
ADD_LIBRARY(GRHthread_A STATIC ${LIBGRHTHREAD_SRC})
TARGET_LINK_LIBRARIES(GRHthread_SO rt)
TARGET_LINK_LIBRARIES(GRHthread_A rt)
SET_TARGET_PROPERTIES(GRHthread_SO PROPERTIES OUTPUT_NAME "gthread" CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(GRHthread_A PROPERTIES OUTPUT_NAME "gthread" CLEAN_DIRECT_OUTPUT 1)
