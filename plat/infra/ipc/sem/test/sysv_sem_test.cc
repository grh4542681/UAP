#include "sem/sem_sysv.h"
#include <stdio.h>
#include <unistd.h>
#include "time/vtime.h"
int main()
{
    printf("hello\n");
    ipc::sem::SemSysV sem("test");
    sem.Create(3,0666);

    sem.V(1,1);
    printf("hello\n");
    sem.P(1,1,&(util::time::Time().SetSecond(2)));
    printf("hello\n");
    sem.P(1,1,&(util::time::Time().SetSecond(2)));
    printf("hello\n");
    sem.Destory();
    printf("hello\n");
    return 0;
}
