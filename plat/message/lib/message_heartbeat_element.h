#ifndef __MESSAGE_HEARTBEAT_ELEMENT_H__
#define __MESSAGE_HEARTBEAT_ELEMENT_H__

#include "mempool.h"
#include "fsm.h"
#include "timer_time.h"

#include "message_uri.h"
#include "message_io.h"

namespace message {

enum class HeartbeatEvent {
    Enable,
    Disable,
    Update,
    Request,
    Response,
};

enum class HeartbeatState {
    Deprecated,
    Closed,
    Establised,
    Inactive,
    Active,
};

class HeartbeatElement {
public:
    HeartbeatElement(const MessageURI& orig_uri, const MessageURI dest_uri, const  timer::Time frequency, unsigned int fault_tolerance);
    ~HeartbeatElement();

private:
    fsm::Fsm<HeartbeatEvent, HeartbeatState> hb_fsm_;

    MessageURI orig_uri_;
    MessageURI dest_uri_;
    timer::Time frequency_;
    unsigned int fault_tolerance_;

    unsigned int fault_num_ = 0;
    timer::Time interval_;
    MessageIO* tunnel_ = nullptr;
};

}

#endif
