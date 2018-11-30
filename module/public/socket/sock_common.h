#ifndef __SOCK_COMMON_H__
#define __SOCK_COMMON_H__

namespace sock {

typedef enum class _SockFamily{
    TCP_LOCAL = 0,
    TCP_INET4,
    TCP_INET6,

    UDP_LOCAL,
    UDP_INET4,
    UDP_INET6,
} SockFamily;

}//namespace sock end

#endif
