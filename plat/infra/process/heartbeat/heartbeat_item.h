#ifndef __HEARTBEAT_ITEM_H__
#define __HEARTBEAT_ITEM_H__

#include "sock_fd.h"

namespace process::heartbeat {

class HeartbeatItem {
public:
    HeartbeatItem();
    ~HeartbeatItem();

private:
    sock::SockFD fd_;

};

}

#endif
