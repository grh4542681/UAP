#lib
ADD_SUBDIRECTORY(infra)
ADD_SUBDIRECTORY(message/lib)
ADD_SUBDIRECTORY(nameserver/lib)

#proc
ADD_SUBDIRECTORY(rm)
#ADD_SUBDIRECTORY(nameserver)
ADD_SUBDIRECTORY(message)

#test
ADD_SUBDIRECTORY(message/lib/test)
