#include "temp_singleton.h"
#include <stdio.h>
int main(){
    int* a = pub::Singleton<int>::getInstance();
    printf("a[%d]\n",*a);
    a = pub::Singleton<int>::getInstance(5);
    printf("a[%d]\n",*a);
    a = pub::Singleton<int>::resetInstance(5);
    printf("a[%d]\n",*a);
    pub::Singleton<int>::delInstance();
    return 0;
}
