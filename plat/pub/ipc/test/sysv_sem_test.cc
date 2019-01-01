#include "sysv_sem.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("hello\n");
    key_t key = ipc::SysVSem::GenKey(".",100);
    ipc::SysVSem sem(key);
    sem.Create();
    sem.P();
    sleep(10);
    sem.V();
    sleep(10);
    sem.Destory();
    return 0;
}
