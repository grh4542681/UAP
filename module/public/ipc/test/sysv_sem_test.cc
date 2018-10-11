#include "sysv_sem.h"
#include <stdio.h>
int main()
{
printf("hello\n");
key_t key = base::SysVSem::GenKey(".",100);
base::SysVSem sem(key);
return 0;
}
