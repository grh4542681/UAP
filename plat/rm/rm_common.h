#ifndef __RM_COMMON_H__
#define __RM_COMMON_H__

#include <list>
#include "rm_return.h"

namespace rm {

typedef enum class _ResourceType {
    IPC_KEY,
    FD,
    MemoryPool,
    ThreadPool,
    ProcessPool,
} ResourceType;

typedef enum class _ControlType {
    IPC_KEY,
    FD,
    MemoryPool,
    ThreadPool,
    ProcessPool,
} ControlType;

} //namespace end

#endif