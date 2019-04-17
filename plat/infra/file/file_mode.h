#ifndef __FILE_MODE_H__
#define __FILE_MODE_H__

#include <string>

#include "file_return.h"

namespace file {

enum class FileMode : int {
    READ_ONLY = 0x01,
    WRITE_ONLY = 0x02,
    READ_WRITE = 0x01 | 0x02,
    CREAT = 0x08,
    EXIST = 0x10,
    TRUNC = 0x20,
    APPEND = 0x40,   
};

int operator|(FileMode a, FileMode b) {
    return ((int)a | (int)b);
}
int operator|(int a, FileMode b) {
    return (a | (int)b);
}
int operator|(FileMode a, int b) {
    return ((int)a | b);
}
bool operator==(int a, FileMode b) {
    return (a == (int)b);
}
bool operator==(FileMode a, int b) {
    return ((int)a == b);
}

class FileModeOp {
public:
    static FileRet FileModeConvert(int mode, std::string& smode) {
        char cmode[16];
        memset(cmode, 0x00, sizeof(cmode));
        if (mode == FileMode::READ_ONLY) {
            sprintf(cmode, "%s", "r");
        } else if (mode == FileMode::WRITE_ONLY) {
            sprintf(cmode, "%s", "w");
        } else if (mode == FileMode::READ_WRITE) {
            sprintf(cmode, "%s", "r+");
        } else if (mode == (FileMode::WRITE_ONLY | FileMode::CREAT)) {
            sprintf(cmode, "%s", "w+");
        } else if (mode == FileMode::APPEND) {
            sprintf(cmode, "%s", "a+");
        } else {
            return FileRet::FILE_EMODE;
        }
        smode.assign(cmode);
        return FileRet::SUCCESS;
    }
    static FileRet FileModeConvert(int mode, unsigned int* pmode) {
        return FileRet::SUCCESS;
    }
private:
    FileModeOp() { }
    ~FileModeOp() { }
};

}

#endif
