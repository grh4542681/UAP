#ifndef __FILE_FD_H__
#define __FILE_FD_H__

namespace file{

class FileFD{
public:
    FileFD(){ }
    virtual ~FileFD(){ }

    virtual int Read(void* data, unsigned int datalen);
    virtual int Write(void* data, unsigned int datalen);
};

}//namespace file end

#endif
