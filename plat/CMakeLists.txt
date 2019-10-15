#lib
ADD_SUBDIRECTORY(infra)
ADD_SUBDIRECTORY(config/lib)
ADD_SUBDIRECTORY(message/lib)
ADD_SUBDIRECTORY(nameserver/lib)

#proc
ADD_SUBDIRECTORY(rm)
#ADD_SUBDIRECTORY(nameserver)
ADD_SUBDIRECTORY(message)

#test
#infra
ADD_SUBDIRECTORY(infra/return/test)
ADD_SUBDIRECTORY(infra/file/test)
ADD_SUBDIRECTORY(infra/mempool/test)
ADD_SUBDIRECTORY(infra/container/test)
ADD_SUBDIRECTORY(infra/parser/test)
ADD_SUBDIRECTORY(infra/socket/test)
ADD_SUBDIRECTORY(infra/thread/test)
ADD_SUBDIRECTORY(infra/process/test)
ADD_SUBDIRECTORY(infra/ipc/shm/test)
ADD_SUBDIRECTORY(infra/ipc/sem/test)
ADD_SUBDIRECTORY(infra/ipc/msg/test)
ADD_SUBDIRECTORY(infra/timer/test)

ADD_SUBDIRECTORY(message/lib/test)
ADD_SUBDIRECTORY(config/lib/test)
