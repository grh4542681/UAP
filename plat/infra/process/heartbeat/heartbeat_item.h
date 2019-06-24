#ifndef __HEARTBEAT_ITEM_H__
#define __HEARTBEAT_ITEM_H__

#include "io_fd.h"
#include "time/vtime.h"
#include "mempool.h"

#include "heartbeat_state.h"

namespace heartbeat {

class HeartbeatItem {
public:
    HeartbeatItem(io::FD& fd, util::time::Time& over_time);
    ~HeartbeatItem();

    io::FD* GetFD();
    HeartbeatState GetState();

    util::time::Time& GetLastTime();
    util::time::Time& GetOverTime();
    util::time::Time& GetDeadTime();

    HeartbeatItem& SetLastTime(util::time::Time& last_time);
    HeartbeatItem& SetOverTime(util::time::Time& over_time);
    HeartbeatItem& SetDeadTime(util::time::Time& dead_time);

private:
    mempool::MemPool* mempool_;
    io::FD* fd_;
    HeartbeatState state_;

    util::time::Time last_time_;
    util::time::Time over_time_;
    util::time::Time dead_time_;

    void (*over_callback_)(void);
    void (*dead_callback_)(void);
};

}

#endif
