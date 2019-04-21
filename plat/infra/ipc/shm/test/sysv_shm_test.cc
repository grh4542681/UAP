#include <unistd.h>
#include "shm/shm_mode.h"
#include "shm/shm_sysv.h"

int main()
{
    ipc::shm::ShmSysV shm(".");
    shm.Create(0666, 1024);
    sleep(10);
    shm.Open(ipc::shm::ShmMode::READ_WRITE);
    sleep(10);
    shm.Close();
    sleep(20);
    shm.Destroy();
    return 0;
}
