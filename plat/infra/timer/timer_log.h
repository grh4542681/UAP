#ifndef __TIMER_LOG_H__
#define __TIMER_LOG_H__

#include <stdio.h>

#define TIMER_DEBUG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define TIMER_LOG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define TIMER_ERROR(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#endif
