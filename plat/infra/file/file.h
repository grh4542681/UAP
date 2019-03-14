#ifndef __FILE_H__
#define __FILE_H__

namespace file{

class File{
public:
    File(){ }
    virtual ~File(){ }

    virtual int Read(void* data, unsigned int datalen);
    virtual int Write(void* data, unsigned int datalen);
};

}//namespace file end

#endif
