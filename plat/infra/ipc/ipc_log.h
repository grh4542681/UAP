#ifndef __IPC_LOG_H__
#define __IPC_LOG_H__

#include <stdio.h>

#define SEM_DEBUG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define SEM_LOG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define SEM_ERROR(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#endif
