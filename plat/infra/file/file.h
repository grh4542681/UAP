#ifndef __FILE_H__
#define __FILE_H__

#include "file_return.h"

namespace file{

class File{
public:
    File(){ }
    virtual ~File(){ }

    virtual FileRet Open(unsigned int mode);
    virtual FileRet Close();
    virtual int Read(void* data, unsigned int datalen);
    virtual int Write(void* data, unsigned int datalen);
};

}//namespace file end

#endif
