#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ipc_mode.h"
#include "shm/shm_list.h"

class AAA {
public:
    int o;
};

int main()
{
    ipc::shm::ShmList<AAA> shmlist("shm_list_test");
    shmlist.Create(10, 0666);
    shmlist.Open(ipc::IpcMode::READ_WRITE);
    printf("%s---%d----%d\n",shmlist.GetObjectName().c_str(),shmlist.GetObjectSize(),shmlist.GetObjectNumber());

    sleep(10);
    shmlist.Close();
    shmlist.Destroy();
    return 0;
}
