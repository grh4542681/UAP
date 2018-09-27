#ifndef __IPC_LOG_H__
#define __IPC_LOG_H__

#include <stdio.h>

#define SEM_DEBUG(fmt, args...)
    printf(fmt, ##args)

#endif
