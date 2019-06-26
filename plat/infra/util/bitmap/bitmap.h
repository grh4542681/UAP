#ifndef __BITMAP_H__
#define __BITMAP_H__

namespace util::bitmap {

class Bitmap {
public:
    Bitmap(size_t bit_size);
    Bitmap(size_t bit_size, long* page_head);
    Bitmap(Bitmap& other);
    ~Bitmap();

    

private;
    bool init_flag_;
    bool free_flag_;

    long* page_head_;
    size_t page_num_;
    size_t bit_max_size_;
    size_t bit_cur_size_;
};

}

#endif
