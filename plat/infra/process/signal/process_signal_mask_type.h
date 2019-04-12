#ifndef __PROCESS_SIGNAL_MASK_TYPE_H__
#define __PROCESS_SIGNAL_MASK_TYPE_H__

#include <signal.h>

namespace process::signal {

enum class SignalMaskType {
    GETMASK,
    APPEND = SIG_BLOCK,
    SUBTRACT = SIG_UNBLOCK,
    REPLACE = SIG_SETMASK,
};

}

#endif
