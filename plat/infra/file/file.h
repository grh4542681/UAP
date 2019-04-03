#ifndef __FILE_H__
#define __FILE_H__

#include <string.h>

#include "file_return.h"

#define FILE_MAX_LINE_LEN (1024)

namespace file{

class File{
public:
    File() { };
    virtual ~File() { };

    virtual FileRet Open(unsigned int mode) { return FileRet::SUCCESS; };
    virtual FileRet Close() { return FileRet::SUCCESS; };
    virtual int Read(void* data, unsigned int datalen) { return 0; };
    virtual int Write(const void* data, unsigned int datalen) { return 0; };

    template <typename ... Args>
    int ReadFmt(const char* fmt, Args&& ... args) {
        char line[FILE_MAX_LINE_LEN];
        memset(line, 0x00, sizeof(line));
        int ret = Read(line, sizeof(line));
        if (ret <= 0) {
            return ret;
        }
        sscanf(line, fmt, std::forward<Args>(args)...);
        return ret;
    };

    template <typename ... Args>
    int WriteFmt(const char* fmt, Args&& ... args) {
        char line[FILE_MAX_LINE_LEN];
        memset(line, 0x00, sizeof(line));
        sprintf(line, fmt, std::forward<Args>(args)...);
        return Write(line, sizeof(line));
    }
};

}//namespace file end

#endif
