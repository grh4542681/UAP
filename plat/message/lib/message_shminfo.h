#ifndef __MESSAGE_SHMINFO_H__
#define __MESSAGE_SHMINFO_H__

namespace message {

template < typename S >
class MessageShminfo {
public:
    MessageShmInfo()

private:
    S shm_;
};

}

#endif
