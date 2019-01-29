#include "hash_table.h"
#include <stdio.h>

int main()
{
    auto lam = [](int x)->unsigned long{ return (unsigned long)x; };
    ds::HashTable<int,decltype(lam)> ht(10, lam);
    ht.insert(4,3);
    printf("size %ld count %ld\n", ht.size(), ht.count());
    return 0;
}
