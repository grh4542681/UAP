#ifndef __BITMAP_H__
#define __BITMAP_H__

#include "mempool.h"
#include "bitmap_return.h"

#define BITMAP_PAGESIZE (8)

namespace util::bitmap {

class Bitmap {
public:
    Bitmap();
    Bitmap(size_t bit_size);
    Bitmap(size_t bit_size, void* bit_head);
    Bitmap(Bitmap& other);
    ~Bitmap();

    size_t GetMaxBitsize();
    size_t GetCurBitsize();

    BitmapRet Set(size_t index);
    BitmapRet Unset(size_t index);
    size_t Find0();
    size_t Find1();
    bool IsFull();

    void Print1();
    void Print0();
    void Print();
private:
    mempool::MemPool* mempool_ = { mempool::MemPool::getInstance() };
    bool free_flag_ = { false };
    void* page_head_ = { NULL };
    size_t page_num_ = { 0 };
    size_t bit_max_size_ = { 0 };
    size_t bit_cur_size_ = { 0 };
};

}

#endif
