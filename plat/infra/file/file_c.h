#ifndef __C_FILE_H__
#define __C_FILE_H__

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "file_log.h"
#include "file_return.h"
#include "file.h"
#include "file_state.h"
#include "file_mode.h"

namespace file{

class FileC : public File {
public:
    FileC(int fd);
    FileC(FILE* ffd);
    FileC(std::string filename);

    ~FileC();

    int GetFd();
    FILE* GetFFd();

    FileRet Open(unsigned int mode);
    FileRet Open(FileMode mode);
    FileRet Close();
    int Read(void* data, unsigned int datalen);
    int Write(const void* data, unsigned int datalen);

    static FileRet GetFileName(int fd, std::string& filename);
    static FileRet GetFileName(FILE* ffd, std::string& filename);
private:
    std::string file_name_;
    int fd_;
    FILE* ffd_;
    FileState state_;

public:
    static FileRet _error2ret(int ierrno) {
        switch (ierrno) {
            case 0:
                return FileRet::SUCCESS;
            case EACCES:
                return FileRet::FILE_EACCES;
            case EFAULT:
                return FileRet::FILE_EFAULT;
            case EINVAL:
                return FileRet::FILE_EINVAL;
            case EIO:
                return FileRet::FILE_EIO;
            case ELOOP:
                return FileRet::FILE_ELOOP;
            case ENAMETOOLONG:
                return FileRet::FILE_ENAMETOOLONG;
            case ENOENT:
                return FileRet::FILE_ENOENT;
            case ENOMEM:
                return FileRet::FILE_ENOMEM;
            case ENOTDIR:
                return FileRet::FILE_ENOTDIR;
            default:
                FILE_ERROR("Unknow errno[%d]", ierrno);
                return FileRet::EUNKOWNERRNO;
        }
    }
};

}//namespcae file end

#endif
