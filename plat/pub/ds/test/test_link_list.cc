#include <stdio.h>
#include "link_list.h"
int main()
{
    ds::LinkList<int> l;
    printf("size %d\n", l.size());
    l.pushback(1);
    l.pushback(2);
    l.pushback(3);
    l.pushback(4);
    l.pushback(5);
    printf("size %d\n", l.size());
    l.pushfront(6);
    l.pushfront(7);
    l.pushfront(8);
    l.pushfront(9);
    l.pushfront(10);
    printf("size %d\n", l.size());
    for (auto it = l.begin(); it != l.end(); it++){
        printf("%d\n", *it);
        if (*it == 5) {
            it.erase();
        }
    }
    for (auto it : l) {
        printf("%d\n", it);
    }
    printf("size %d\n", l.size());

    return 0;
}
