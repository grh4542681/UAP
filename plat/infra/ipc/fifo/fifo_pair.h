#ifndef __FIFO_PAIR_H__
#define __FIFO_PAIR_H__

#include "ipc_log.h"
#include "ipc_return.h"

#include "fifo_fd.h"

namespace ipc::fifo {

class FifoPair {
public:
    FifoPair();
    FifoPair(const FifoPair& other);
    ~FifoPair();

    IpcRet Open();
    void Close();

    FifoFD& operator[] (const unsigned int index);
    FifoPair& operator= (const FifoPair& other);

private:
    bool init_flag_;
    FifoFD fds_[3];
    
};

}

#endif
