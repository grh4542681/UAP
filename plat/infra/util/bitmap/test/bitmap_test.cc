#include "bitmap/bitmap.h"

int main()
{
    util::bitmap::Bitmap bm(10);
    printf("%d---%d-----%d\n",bm.page_num_,bm.bit_max_size_,bm.bit_cur_size_);
    bm.Set(8);
    bm.Set(7);
    printf("%d---%d-----%d\n",bm.page_num_,bm.bit_max_size_,bm.bit_cur_size_);
    bm.Print();
    bm.Set(9);
    bm.Set(11);
    printf("%d---%d-----%d\n",bm.page_num_,bm.bit_max_size_,bm.bit_cur_size_);
    bm.Unset(5);
    printf("%d---%d-----%d\n",bm.page_num_,bm.bit_max_size_,bm.bit_cur_size_);
    bm.Print();
    return 0;
}
