#include "sysv_sem.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("hello\n");
    key_t key = base::SysVSem::GenKey(".",100);
    base::SysVSem sem(key);
    sem.create();
    sem.P();
    sleep(10);
    sem.V();
    sleep(10);
    sem.destory();
    return 0;
}
