#ifndef __FILE_H__
#define __FILE_H__

#include "file_return.h"

namespace file{

class File{
public:
    File() { };
    virtual ~File() { };

    virtual FileRet Open(unsigned int mode) { return FileRet::SUCCESS; };
    virtual FileRet Close() { return FileRet::SUCCESS; };
    virtual int Read(void* data, unsigned int datalen) { return 0; };
    virtual int Write(const void* data, unsigned int datalen) { return 0; };
};

}//namespace file end

#endif
