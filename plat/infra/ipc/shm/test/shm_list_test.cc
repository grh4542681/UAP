#include <stdio.h>
#include <string.h>

#include "ipc_mode.h"
#include "shm/shm_list.h"

int main()
{
    ipc::shm::ShmList<int> shmlist("shm_list_test");
    shmlist.Create(10, 0666);
    return 0;
}
