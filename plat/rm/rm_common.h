#ifndef __RM_COMMON_H__
#define __RM_COMMON_H__

#include "rm_return.h"

namespace rm {

typedef enum class _ResourceType {
    SYSV_IPC_KEY,
    FD,
    MemoryPool,
    ThreadPool,
    ProcessPool,
} ResourceType;

typedef enum class _ControlType {
    CREATE,
    DELETE,
    UPDATE,
    SELECT,
} ControlType;

} //namespace end

#endif
