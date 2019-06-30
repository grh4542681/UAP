#include "bitmap/bitmap.h"

int main()
{
    size_t i;
    util::bitmap::Bitmap bm(10);
    bm.Set(2);
    bm.Print();
    bm.Set(8);
    bm.Print();
    bm.Set(7);
    bm.Print();
    bm.Set(9);
    bm.Print();
    bm.Print1();
    printf("1---%d\n", bm.Find1());
    i = bm.Find1();
    bm.Unset(i);
    bm.Print();
    printf("1---%d\n", bm.Find1());
    printf("0---%d\n", bm.Find0());
    i = bm.Find0();
    bm.Set(i);
    bm.Print();
    printf("0---%d\n", bm.Find0());
    i = bm.Find0();
    bm.Set(i);
    bm.Print();
    printf("0---%d\n", bm.Find0());
    return 0;
}
