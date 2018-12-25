#ifndef __SOCK_COMMON_H__
#define __SOCK_COMMON_H__

namespace sock {

#define SOCK_ADDRESS_MAX_LEN (256)

typedef enum class _SockFamily{
    TCP_LOCAL = 0,
    TCP_INET4,
    TCP_INET6,

    UDP_LOCAL,
    UDP_INET4,
    UDP_INET6,
    
    MULTICAST_INET4,
    MULTICAST_INET6,
} SockFamily;

}//namespace sock end

#endif
