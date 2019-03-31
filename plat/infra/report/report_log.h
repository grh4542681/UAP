#ifndef __REPORT_LOG_H__
#define __REPORT_LOG_H__

#include <stdio.h>

#define REPORT_DEBUG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define REPORT_LOG(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#define REPORT_ERROR(fmt, args...) \
    printf("%s[%d]: ", __func__, __LINE__); \
    printf(fmt, ##args); \
    printf("\n");

#endif
