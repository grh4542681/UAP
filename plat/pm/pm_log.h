#ifndef __PM_LOG_H__
#define __PM_LOG_H__

#include <stdio.h>

#define PM_DEBUG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define PM_LOG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define PM_ERROR(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#endif
