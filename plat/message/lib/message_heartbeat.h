#ifndef __MESSAGE_HEARTBEAT_H__
#define __MESSAGE_HEARTBEAT_H__

#include "io_auto_select.h"
#include "thread_template.h"

#include "message_return.h"
#include "message_uri.h"
#include "message_remote.h"
#include "message_internal.h"

#include "message_heartbeat_element.h"

namespace message {

class HeartbeatClient {
public:
    HeartbeatClient();
    ~HeartbeatClient();

    MessageRet Add(HeartbeatElement& element);
    MessageRet Del(MessageURI uri);
private:
private:
    io::AutoSelect select_;
//std::map<timer::TimerFD, std::vector<HeartbeatElement>> timer_element_;
};

class HeartbeatServer {

};

}

#endif
