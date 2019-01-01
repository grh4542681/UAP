#include "sysv_array_shm.h"

namespace ipc {

template <typename T>
SysVArrayShm::SysVArrayShm(key_t key, size_t size):SysVShm(key, size)
{
    this->init_flag_ = false;
    this->block_size_ = sizeof(T);
    this->block_num_ = this->size_ / this->block_size_;
    this->init_flag_ = true;
}

template <typename T>
SysVArrayShm::SysVArrayShm(key_t key, size_t size, mode_t mode):SysVShm(key, size, mode)
{
    this->init_flag_ = false;
    this->block_size_ = sizeof(T);
    this->block_num_ = this->size_ / this->block_size_;
    this->init_flag_ = true;
}

SysVArrayShm::~SysVArrayShm()
{

}

T* SysVArrayShm::get(unsigned int index)
{

}

T* SysVArrayShm::set(unsigned int index, T* data)
{

}

}; //namespace end