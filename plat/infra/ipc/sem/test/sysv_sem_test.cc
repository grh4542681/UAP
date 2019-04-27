#include "sem/sem_sysv.h"
#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("hello\n");
    ipc::sem::SemSysV sem("test");
    sem.Create(3,0666);
    sem.P(1,1,NULL);
    sleep(10);
    sem.V(1,1);
    sleep(10);
    sem.Destory();
    return 0;
}
