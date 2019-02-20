#include "hash_table.h"
#include <stdio.h>

int main()
{
    auto lam = [](int x)->unsigned long{ return (unsigned long)x; };
    ds::HashTable<int,decltype(lam)> ht(10, lam);
    ht.insert(4,3);
    printf("size %ld count %ld free %ld\n", ht.size(), ht.count(), ht.available());
    int* test = ht.find(3);
    printf("get value[%d]\n", *test);
    ht.insert(5,3);
    ht.insert(5,4);
    ht.insert(5,5);
    printf("get value[%d]\n", *test);
    ht.remove(3);
    printf("get value[%d]\n", *test);
    printf("size %ld count %ld free %ld\n", ht.size(), ht.count(), ht.available());
    ht.clear();
    printf("size %ld count %ld free %ld\n", ht.size(), ht.count(), ht.available());
    return 0;
}
