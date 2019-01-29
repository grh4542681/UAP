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
    for (auto it : l) {
        printf("%d\n", it);
    }
    printf("=============================\n");
    for (auto it = l.begin(); it != l.end(); ++it){
        if (*it == 7 || *it == 8 || *it ==5 || *it == 10) {
            l.pop(it);
        }
    }
    for (auto it : l) {
        printf("%d\n", it);
    }
    printf("size %d\n", l.size());
    printf("=============================\n");
    l.popfront();
    l.popback();
    for (auto it : l) {
        printf("%d\n", it);
    }
    printf("size %d\n", l.size());
    printf("=============================\n");
    l.clear();
    printf("size %d\n", l.size());
    struct aaa {
        int i;
        char a;
    };
    struct aaa test1 = { 1,'1'};
    ds::LinkList<struct aaa> l2;
    l2.pushback(test1);
    printf("size %d\n", l2.size());
    for (auto it : l2) {
        printf("%d\n", it.i);
    }

    return 0;
}
