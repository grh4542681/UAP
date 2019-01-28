#include "hash_table.h"

int main()
{
    ds::HashTable<int> ht(10, [](int& x)->unsigned long{ return (unsigned long)x; });
    return 0;
}
