#ifndef __SYSV_ARRAY_SHM_H__
#define __SYSV_ARRAY_SHM_H__

#include "sysv_shm.h"

namespace ipc {

template <typename T>
class SysVArrayShm : public SysVShm {
public:
    SysVArrayShm(key_t key, size_t size);
    SysVArrayShm(key_t key, size_t size, mode_t mode);
    ~SysVArrayShm();

    T* get(unsigned int index);
    T* set(unsigned int index, T* data);

    T& operator[](int index);

private:
    bool init_flag_;
    unsigned int block_num_;
    unsigned int block_size_;
};

} //namespace ipc end

#endif