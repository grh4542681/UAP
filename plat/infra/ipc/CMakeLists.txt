SET(LIBGRHIPC_SRC shm/shm_mode.cc
                  shm/shm_sysv.cc
                  shm/shm_posix.cc
                  socket/sock_pair.cc
                  )

ADD_LIBRARY(GRHipc_SO SHARED ${LIBGRHIPC_SRC})
SET_TARGET_PROPERTIES(GRHipc_SO PROPERTIES OUTPUT_NAME "gipc" CLEAN_DIRECT_OUTPUT 1)
TARGET_LINK_LIBRARIES(GRHipc_SO rt)

