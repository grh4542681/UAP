#ifndef __MESSAGE_DEFINES_H__
#define __MESSAGE_DEFINES_H__

#include "common_defines.h"

#define MESSAGE_ENDPOINT_NAME_MAX_LEN (128)
#define MESSAGE_DEAMON_SOCK_FILE ("tmp/messaged.sock")
#define MESSAGE_DEAMON_SOCK_FILE_PATH (PLATFORM_ROOT_DIR ## MESSAGE_DEAMON_SOCK_FILE)

enum class MessageClientState {
    CONNECTED,
    DISCONNECTED,
};

#endif
