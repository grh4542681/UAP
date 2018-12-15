#include "temp_multiton.h"
#include <stdio.h>
int main(){
    int* a = base::Multiton<int,int>::getInstance(1);
    printf("a[%d]\n",*a);
    a = base::Multiton<int,int>::getInstance(2,5);
    printf("a[%d]\n",*a);
    a = base::Multiton<int,int>::resetInstance(1,5);
    printf("a[%d]\n",*a);
    printf("size[%d]\n",base::Multiton<int,int>::getSize());
    base::Multiton<int,int>::delInstance(1);
    printf("size[%d]\n",base::Multiton<int,int>::getSize());
    a = base::Multiton<int,int>::getInstance(1,6);
    printf("a[%d]\n",*a);
    base::Multiton<int,int>::delInstance(1);
    return 0;
}
