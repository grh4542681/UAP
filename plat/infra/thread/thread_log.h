#ifndef __THREAD_LOG_H__
#define __THREAD_LOG_H__

#include <stdio.h>

#define THREAD_DEBUG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define THREAD_LOG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define THREAD_ERROR(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#endif
