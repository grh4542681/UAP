SET(LIBGRHIPC_SRC ipc_mode.cc
                  ipc_return.cc
                  shm/shm_sysv.cc
                  shm/shm_posix.cc
                  sem/sem_sysv.cc
                  sem/sem_posix.cc
                  msg/msg_shm.cc
                  socket/sock_pair.cc
                  event/event_fd.cc
                  event/event_semaphore.cc
                  )

ADD_LIBRARY(GRHipc_SO SHARED ${LIBGRHIPC_SRC})
SET_TARGET_PROPERTIES(GRHipc_SO PROPERTIES OUTPUT_NAME "gipc" CLEAN_DIRECT_OUTPUT 1)
TARGET_LINK_LIBRARIES(GRHipc_SO rt)

