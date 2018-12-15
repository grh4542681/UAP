#include "temp_singleton.h"
#include <stdio.h>
int main(){
    int* a = base::Singleton<int>::getInstance();
    printf("a[%d]\n",*a);
    a = base::Singleton<int>::getInstance(5);
    printf("a[%d]\n",*a);
    a = base::Singleton<int>::resetInstance(5);
    printf("a[%d]\n",*a);
    base::Singleton<int>::delInstance();
    return 0;
}
