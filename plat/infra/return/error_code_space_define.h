#ifndef __ERROR_CODE_SPACE_DEFINE_H__
#define __ERROR_CODE_SPACE_DEFINE_H__

#define ERROR_CODE_BASE (0x00000000)
#define ERROR_CODE_SPACE (0x00000100)                                                                                                                                                    

#define PUBLIC_ERROR_CODE_BASE (ERROR_CODE_BASE + ERROR_CODE_SPACE)
#define SOCKET_ERROR_CODE_BASE (PUBLIC_ERROR_CODE_BASE + ERROR_CODE_SPACE)

#endif
