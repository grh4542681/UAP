#ifndef __ERROR_CODE_SPACE_DEFINE_H__
#define __ERROR_CODE_SPACE_DEFINE_H__

// 0 ~ 0x00001000 is system errno
#define ERROR_CODE_BASE (0x00001000)
#define ERROR_CODE_SPACE (0x00000100)                                                                                                                                                    

#define PUBLIC_ERROR_CODE_BASE  (ERROR_CODE_BASE + (ERROR_CODE_SPACE * 1))
#define SOCKET_ERROR_CODE_BASE  (ERROR_CODE_BASE + (ERROR_CODE_SPACE * 2))
#define IO_ERROR_CODE_BASE      (ERROR_CODE_BASE + (ERROR_CODE_SPACE * 3))
#define IPC_ERROR_CODE_BASE     (ERROR_CODE_BASE + (ERROR_CODE_SPACE * 4))
#endif
