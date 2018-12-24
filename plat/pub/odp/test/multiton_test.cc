#include "temp_multiton.h"
#include <stdio.h>
int main(){
    int* a = pub::Multiton<int,int>::getInstance(1);
    printf("a[%d]\n",*a);
    a = pub::Multiton<int,int>::getInstance(2,5);
    printf("a[%d]\n",*a);
    a = pub::Multiton<int,int>::resetInstance(1,5);
    printf("a[%d]\n",*a);
    printf("size[%d]\n",pub::Multiton<int,int>::getSize());
    pub::Multiton<int,int>::delInstance(1);
    printf("size[%d]\n",pub::Multiton<int,int>::getSize());
    a = pub::Multiton<int,int>::getInstance(1,6);
    printf("a[%d]\n",*a);
    pub::Multiton<int,int>::delInstance(1);
    return 0;
}
