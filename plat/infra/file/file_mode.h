#ifndef __FILE_MODE_H__
#define __FILE_MODE_H__

#include <string>

#include "file_return.h"

namespace file {

enum class FileMode : int {
    READ_ONLY = 0x01,
    WRITE_ONLY = 0x02,
    READ_WRITE = 0x04,
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

class FileModeOp {
public:
    static FileRet FileModeConvert(unsigned int mode, std::string& smode) {

    }
    static FileRet FileModeConvert(unsigned int mode, unsigned int* pmode) {

    }
private:
    FileModeOp() { }
    ~FileModeOp() { }
};

}

#endif