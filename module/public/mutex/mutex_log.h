#ifndef __IPC_LOG_H__
#define __IPC_LOG_H__

#include <stdio.h>

#define MUTEX_DEBUG(fmt, args...) \
    printf(fmt, ##args)

#define MUTEX_INFO(fmt, args...) \
    printf(fmt, ##args)

#define MUTEX_ERROR(fmt, args...) \
    printf(fmt, ##args)

#endif
